#include "scheduler.h"

#include "stack_thread.h"

#include <thread>

#include <stdexcept>

thread_local bool TaskScheduler::tls_in_worker_{false};

namespace {

size_t default_workers() {
  unsigned hc = std::thread::hardware_concurrency();
  if (hc == 0) return 4;
  return hc < 2 ? 2 : static_cast<size_t>(hc);
}

void* run_std_function_void(void* p) {
  auto* f = static_cast<std::function<void()>*>(p);
  (*f)();
  delete f;
  return nullptr;
}

}  // namespace

void* TaskScheduler::worker_entry(void* self) {
  static_cast<TaskScheduler*>(self)->workerLoop();
  return nullptr;
}

TaskScheduler::TaskScheduler(size_t num_workers) {
  num_workers_ = num_workers == 0 ? default_workers() : num_workers;
  workers_.resize(num_workers_);
  constexpr size_t kStack = 8u * 1024u * 1024u;
  for (size_t i = 0; i < num_workers_; ++i) {
    if (!start_pthread_with_stack(kStack, worker_entry, this, &workers_[i])) {
      throw std::runtime_error("failed to start worker thread");
    }
  }
}

TaskScheduler::~TaskScheduler() {
  {
    std::lock_guard<std::mutex> lk(mu_);
    stop_ = true;
  }
  cv_.notify_all();
  for (pthread_t w : workers_) {
    pthread_join(w, nullptr);
  }
}

bool TaskScheduler::in_worker_thread() { return tls_in_worker_; }

void TaskScheduler::set_quantum_budget(size_t budget) {
  if (budget == 0) {
    throw std::runtime_error("scheduler quantum budget must be > 0");
  }
  quantum_budget_.store(budget);
}

void TaskScheduler::enqueueTask(std::shared_ptr<ScheduledTask> task) {
  {
    std::lock_guard<std::mutex> lk(mu_);
    queue_.push(std::move(task));
  }
  cv_.notify_one();
}

void TaskScheduler::finishTask(const std::shared_ptr<ScheduledTask>& task, const Value& value, TaskStatus status) {
  task->handle->status.store(status);
  task->handle->metrics.completed_at = std::chrono::steady_clock::now();
  task->promise->set_value(value);
}

void TaskScheduler::failTask(const std::shared_ptr<ScheduledTask>& task, TaskStatus status) {
  task->handle->status.store(status);
  task->handle->metrics.completed_at = std::chrono::steady_clock::now();
  if (status == TaskStatus::Cancelled) {
    task->promise->set_exception(std::make_exception_ptr(std::runtime_error("task cancelled")));
    return;
  }
  task->promise->set_exception(std::current_exception());
}

void TaskScheduler::workerLoop() {
  tls_in_worker_ = true;
  while (true) {
    std::shared_ptr<ScheduledTask> task;
    {
      std::unique_lock<std::mutex> lk(mu_);
      cv_.wait(lk, [&] { return stop_ || !queue_.empty(); });
      if (stop_ && queue_.empty()) {
        break;
      }
      if (!queue_.empty()) {
        task = std::move(queue_.front());
        queue_.pop();
      }
    }
    if (!task) {
      continue;
    }
    if (task->handle->cancel_requested.load()) {
      failTask(task, TaskStatus::Cancelled);
      continue;
    }
    if (task->handle->metrics.run_slices == 0) {
      task->handle->metrics.first_started_at = std::chrono::steady_clock::now();
    }
    task->handle->status.store(TaskStatus::Running);
    task->handle->metrics.run_slices++;

    try {
      RunSliceResult result = task->run_slice(task->handle, quantum_budget_.load());
      task->handle->metrics.checkpoint_count += result.checkpoints;
      if (result.status == RunSliceResult::Status::Yielded && result.continuation) {
        task->handle->status.store(TaskStatus::Yielded);
        task->handle->metrics.yield_count++;
        task->handle->continuation = std::make_shared<ContinuationState>();
        task->handle->continuation->frame_id = task->handle->metrics.run_slices;
        auto continuation = std::move(result.continuation);
        task->run_slice = [cont = std::move(continuation)](const std::shared_ptr<TaskObject>& handle,
                                                           size_t budget) mutable { return cont(handle, budget); };
        enqueueTask(std::move(task));
      } else {
        task->handle->continuation.reset();
        finishTask(task, result.value, TaskStatus::Completed);
      }
    } catch (...) {
      failTask(task, TaskStatus::Failed);
    }
  }
  tls_in_worker_ = false;
}

Value TaskScheduler::submitPreemptible(
    std::function<RunSliceResult(const std::shared_ptr<TaskObject>&, size_t)> run_slice) {
  auto prom = std::make_shared<std::promise<Value>>();
  std::future<Value> fut = prom->get_future();
  auto handle = std::make_shared<TaskObject>();
  handle->future = std::move(fut);
  handle->status.store(TaskStatus::Ready);

  auto scheduled = std::make_shared<ScheduledTask>();
  scheduled->handle = handle;
  scheduled->promise = prom;
  scheduled->run_slice = std::move(run_slice);

  if (tls_in_worker_) {
    auto fp = new std::function<void()>([scheduled, this]() {
      // Overflow path keeps nested scheduling from starving small pools.
      try {
        for (;;) {
          if (scheduled->handle->cancel_requested.load()) {
            failTask(scheduled, TaskStatus::Cancelled);
            return;
          }
          if (scheduled->handle->metrics.run_slices == 0) {
            scheduled->handle->metrics.first_started_at = std::chrono::steady_clock::now();
          }
          scheduled->handle->status.store(TaskStatus::Running);
          scheduled->handle->metrics.run_slices++;
          RunSliceResult result = scheduled->run_slice(scheduled->handle, quantum_budget_.load());
          scheduled->handle->metrics.checkpoint_count += result.checkpoints;
          if (result.status == RunSliceResult::Status::Yielded && result.continuation) {
            scheduled->handle->status.store(TaskStatus::Yielded);
            scheduled->handle->metrics.yield_count++;
            scheduled->handle->continuation = std::make_shared<ContinuationState>();
            scheduled->handle->continuation->frame_id = scheduled->handle->metrics.run_slices;
            auto continuation = std::move(result.continuation);
            scheduled->run_slice =
                [cont = std::move(continuation)](const std::shared_ptr<TaskObject>& handle,
                                                 size_t budget) mutable { return cont(handle, budget); };
            continue;
          }
          scheduled->handle->continuation.reset();
          finishTask(scheduled, result.value, TaskStatus::Completed);
          return;
        }
      } catch (...) {
        failTask(scheduled, TaskStatus::Failed);
      }
    });
    pthread_t tid{};
    constexpr size_t kStack = 8u * 1024u * 1024u;
    if (!start_pthread_with_stack(kStack, run_std_function_void, fp, &tid)) {
      delete fp;
      throw std::runtime_error("failed to start overflow thread");
    }
    handle->overflow_pthread = tid;
    handle->has_overflow_pthread = true;
    return Value::makeTask(handle);
  }

  enqueueTask(std::move(scheduled));
  return Value::makeTask(handle);
}

Value TaskScheduler::submit(std::function<Value()> work) {
  return submitPreemptible([w = std::move(work)](const std::shared_ptr<TaskObject>&, size_t) mutable {
    RunSliceResult result;
    result.status = RunSliceResult::Status::Completed;
    result.value = w();
    return result;
  });
}
