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

void TaskScheduler::workerLoop() {
  tls_in_worker_ = true;
  while (true) {
    std::function<void()> job;
    {
      std::unique_lock<std::mutex> lk(mu_);
      cv_.wait(lk, [&] { return stop_ || !queue_.empty(); });
      if (stop_ && queue_.empty()) {
        break;
      }
      if (!queue_.empty()) {
        job = std::move(queue_.front());
        queue_.pop();
      }
    }
    if (job) {
      job();
    }
  }
  tls_in_worker_ = false;
}

Value TaskScheduler::submit(std::function<Value()> work) {
  auto prom = std::make_shared<std::promise<Value>>();
  std::future<Value> fut = prom->get_future();
  auto handle = std::make_shared<TaskObject>();
  handle->future = std::move(fut);

  auto run = [prom, work = std::move(work)]() mutable {
    try {
      Value v = work();
      prom->set_value(std::move(v));
    } catch (...) {
      try {
        prom->set_exception(std::current_exception());
      } catch (...) {
      }
    }
  };

  if (tls_in_worker_) {
    auto fp = new std::function<void()>(std::move(run));
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

  {
    std::lock_guard<std::mutex> lk(mu_);
    queue_.push(std::move(run));
  }
  cv_.notify_one();
  return Value::makeTask(handle);
}
