#include "scheduler.h"

#include "evaluator.h"
#include "stack_thread.h"

#include <stdexcept>
#include <thread>
#include <utility>

thread_local bool TaskScheduler::tls_in_worker_{false};

namespace {

size_t default_workers() {
  unsigned hc = std::thread::hardware_concurrency();
  if (hc == 0) return 4;
  return hc < 2 ? 2 : static_cast<size_t>(hc);
}

}  // namespace

void* TaskScheduler::worker_entry(void* self) {
  static_cast<TaskScheduler*>(self)->workerLoop();
  return nullptr;
}

void* TaskScheduler::timer_entry(void* self) {
  static_cast<TaskScheduler*>(self)->timerLoop();
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
  if (!start_pthread_with_stack(kStack, timer_entry, this, &timer_thread_)) {
    throw std::runtime_error("failed to start timer thread");
  }
  timer_started_ = true;
}

TaskScheduler::~TaskScheduler() {
  std::vector<std::shared_ptr<ScheduledTask>> to_fail;
  {
    std::lock_guard<std::mutex> lk(mu_);
    stop_ = true;
    while (!queue_.empty()) {
      to_fail.push_back(std::move(queue_.front()));
      queue_.pop();
    }
  }
  {
    std::lock_guard<std::mutex> lk(delay_mu_);
    while (!delay_queue_.empty()) {
      to_fail.push_back(delay_queue_.top().task);
      delay_queue_.pop();
    }
  }
  for (auto& t : to_fail) {
    if (!t || !t->handle) continue;
    if (isTerminalStatus(t->handle->status.load())) continue;
    try {
      failTask(t, TaskStatus::Cancelled);
    } catch (...) {
    }
  }
  delay_cv_.notify_all();
  cv_.notify_all();
  if (timer_started_) {
    pthread_join(timer_thread_, nullptr);
  }
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
    if (stop_) {
      return;
    }
    queue_.push(std::move(task));
  }
  cv_.notify_one();
}

void TaskScheduler::finishTask(const std::shared_ptr<ScheduledTask>& task, const Value& value,
                               TaskStatus status) {
  std::vector<std::shared_ptr<ScheduledTask>> waiters;
  {
    std::lock_guard<std::mutex> lk(task->handle->mu);
    task->handle->result_value = value;
    task->handle->result_error = nullptr;
    task->handle->has_result = true;
    task->handle->status.store(status);
    task->handle->metrics.completed_at = std::chrono::steady_clock::now();
    task->handle->parked_scheduled.reset();
    waiters.swap(task->handle->waiters);
  }
  try {
    task->promise->set_value(value);
  } catch (...) {
  }
  for (auto& w : waiters) {
    if (!w || !w->handle) continue;
    if (isTerminalStatus(w->handle->status.load())) continue;
    if (w->handle->cancel_requested.load()) {
      failTask(w, TaskStatus::Cancelled);
      continue;
    }
    w->pending_resume = value;
    w->pending_error = nullptr;
    w->has_pending_resume = true;
    {
      std::lock_guard<std::mutex> lk(w->handle->mu);
      w->handle->parked_scheduled.reset();
    }
    enqueueTask(w);
  }
}

void TaskScheduler::failTask(const std::shared_ptr<ScheduledTask>& task, TaskStatus status) {
  std::exception_ptr err;
  if (status == TaskStatus::Cancelled) {
    err = std::make_exception_ptr(std::runtime_error("task cancelled"));
  } else {
    err = std::current_exception();
    if (!err) {
      err = std::make_exception_ptr(std::runtime_error("task failed"));
    }
  }
  std::vector<std::shared_ptr<ScheduledTask>> waiters;
  {
    std::lock_guard<std::mutex> lk(task->handle->mu);
    if (isTerminalStatus(task->handle->status.load()) && task->handle->has_result) {
      return;
    }
    task->handle->result_value = Value::null();
    task->handle->result_error = err;
    task->handle->has_result = true;
    task->handle->status.store(status);
    task->handle->metrics.completed_at = std::chrono::steady_clock::now();
    task->handle->parked_scheduled.reset();
    waiters.swap(task->handle->waiters);
  }
  try {
    task->promise->set_exception(err);
  } catch (...) {
  }
  for (auto& w : waiters) {
    if (!w || !w->handle) continue;
    if (isTerminalStatus(w->handle->status.load())) continue;
    if (w->handle->cancel_requested.load()) {
      failTask(w, TaskStatus::Cancelled);
      continue;
    }
    w->pending_resume = Value::null();
    w->pending_error = err;
    w->has_pending_resume = true;
    {
      std::lock_guard<std::mutex> lk(w->handle->mu);
      w->handle->parked_scheduled.reset();
    }
    enqueueTask(w);
  }
}

void TaskScheduler::armResumeSlice(std::shared_ptr<ScheduledTask> task,
                                   std::function<Value(const Value&)> resume_cont) {
  auto self = shared_from_this();
  std::shared_ptr<ScheduledTask> st = std::move(task);
  st->run_slice = [self, st, resume_cont = std::move(resume_cont)](
                      const std::shared_ptr<TaskObject>& handle, size_t budget) mutable {
    Value pending = st->pending_resume;
    std::exception_ptr pending_error = st->pending_error;
    st->has_pending_resume = false;
    st->pending_error = nullptr;
    st->pending_resume = Value::null();
    return runResumeSlice(self, handle, budget, resume_cont, std::move(pending), pending_error);
  };
}

void TaskScheduler::parkOnDelay(std::shared_ptr<ScheduledTask> task,
                                std::chrono::steady_clock::time_point wake_at) {
  task->handle->status.store(TaskStatus::Waiting);
  uint64_t gen = 0;
  {
    std::lock_guard<std::mutex> lk(task->handle->mu);
    task->handle->delay_generation++;
    gen = task->handle->delay_generation;
    task->handle->parked_scheduled = task;
  }
  {
    std::lock_guard<std::mutex> lk(delay_mu_);
    delay_queue_.push(DelayItem{wake_at, gen, task});
  }
  delay_cv_.notify_one();
}

void TaskScheduler::parkOnJoin(std::shared_ptr<ScheduledTask> task,
                               const std::shared_ptr<TaskObject>& target) {
  Value ready_value = Value::null();
  std::exception_ptr ready_error;
  bool already_done = false;
  {
    std::lock_guard<std::mutex> lk(target->mu);
    if (target->has_result) {
      already_done = true;
      ready_value = target->result_value;
      ready_error = target->result_error;
    } else {
      task->handle->status.store(TaskStatus::Waiting);
      {
        std::lock_guard<std::mutex> lk2(task->handle->mu);
        task->handle->parked_scheduled = task;
      }
      target->waiters.push_back(task);
    }
  }
  if (already_done) {
    if (task->handle->cancel_requested.load()) {
      failTask(task, TaskStatus::Cancelled);
      return;
    }
    task->pending_resume = ready_value;
    task->pending_error = ready_error;
    task->has_pending_resume = true;
    enqueueTask(std::move(task));
  }
}

bool TaskScheduler::cancelParkedLocked(const std::shared_ptr<TaskObject>& handle,
                                       std::vector<std::shared_ptr<ScheduledTask>>* out_fail) {
  auto st = handle->status.load();
  if (st != TaskStatus::Waiting) {
    return false;
  }
  auto parked = handle->parked_scheduled.lock();
  if (!parked) {
    return false;
  }
  // Invalidate delay entries via generation bump.
  handle->delay_generation++;
  handle->parked_scheduled.reset();
  out_fail->push_back(parked);
  return true;
}

void TaskScheduler::requestCancel(const std::shared_ptr<TaskObject>& handle) {
  handle->cancel_requested.store(true);
  std::vector<std::shared_ptr<ScheduledTask>> to_fail;
  {
    std::lock_guard<std::mutex> lk(handle->mu);
    cancelParkedLocked(handle, &to_fail);
  }
  // Also remove ourselves from any join-target waiter lists by bumping generation only for delay;
  // for join waiters, finish/fail of target still wakes us — check cancel then.
  // If we are Waiting on join, we need to remove from target's waiters. We don't store the
  // join target on TaskObject; arming cancel means when woken we fail. If still Waiting, try
  // fail immediately via parked_scheduled.
  for (auto& t : to_fail) {
    failTask(t, TaskStatus::Cancelled);
  }
  // If Waiting on join (parked still set was cleared only for delay path above — join also sets
  // parked_scheduled). cancelParkedLocked already collected join-parked tasks.
  delay_cv_.notify_all();
}

void TaskScheduler::timerLoop() {
  while (true) {
    std::shared_ptr<ScheduledTask> due;
    {
      std::unique_lock<std::mutex> lk(delay_mu_);
      if (stop_ && delay_queue_.empty()) {
        break;
      }
      if (delay_queue_.empty()) {
        delay_cv_.wait(lk, [&] { return stop_ || !delay_queue_.empty(); });
        if (stop_ && delay_queue_.empty()) {
          break;
        }
        continue;
      }
      auto wake = delay_queue_.top().wake_at;
      auto now = std::chrono::steady_clock::now();
      if (wake > now) {
        delay_cv_.wait_until(lk, wake, [&] {
          return stop_ || delay_queue_.empty() || delay_queue_.top().wake_at <= std::chrono::steady_clock::now();
        });
        if (stop_ && delay_queue_.empty()) {
          break;
        }
        continue;
      }
      DelayItem item = delay_queue_.top();
      delay_queue_.pop();
      due = item.task;
      // Drop stale generations (cancelled or re-parked).
      if (due && due->handle) {
        std::lock_guard<std::mutex> hlk(due->handle->mu);
        if (item.generation != due->handle->delay_generation) {
          due.reset();
        }
      }
    }
    if (!due) {
      continue;
    }
    if (due->handle->cancel_requested.load()) {
      failTask(due, TaskStatus::Cancelled);
      continue;
    }
    due->pending_resume = Value::null();
    due->pending_error = nullptr;
    due->has_pending_resume = true;
    due->handle->parked_scheduled.reset();
    enqueueTask(std::move(due));
  }
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
                                                           size_t budget) mutable {
          return cont(handle, budget);
        };
        enqueueTask(std::move(task));
      } else if (result.status == RunSliceResult::Status::Suspended && result.resume_continuation) {
        if (task->handle->cancel_requested.load()) {
          failTask(task, TaskStatus::Cancelled);
        } else {
          armResumeSlice(task, std::move(result.resume_continuation));
          if (result.suspend_kind == SuspendRequest::Kind::Delay) {
            parkOnDelay(std::move(task), result.wake_at);
          } else {
            parkOnJoin(std::move(task), result.join_target);
          }
        }
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
  handle->scheduler = shared_from_this();

  auto scheduled = std::make_shared<ScheduledTask>();
  scheduled->handle = handle;
  scheduled->promise = prom;
  scheduled->run_slice = std::move(run_slice);

  // Always enqueue onto the shared pool (Kotlin-style); park-on-join frees carriers.
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
