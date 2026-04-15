#pragma once

#include "object.h"

#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <pthread.h>
#include <queue>
#include <vector>

struct RunSliceResult {
  enum class Status { Completed, Yielded };
  Status status{Status::Completed};
  Value value{Value::null()};
  std::function<RunSliceResult(const std::shared_ptr<TaskObject>&, size_t)> continuation;
  uint64_t checkpoints{0};
};

struct ScheduledTask {
  std::shared_ptr<TaskObject> handle;
  std::shared_ptr<std::promise<Value>> promise;
  std::function<RunSliceResult(const std::shared_ptr<TaskObject>&, size_t)> run_slice;
};

class TaskScheduler : public std::enable_shared_from_this<TaskScheduler> {
 public:
  explicit TaskScheduler(size_t num_workers);
  ~TaskScheduler();

  Value submit(std::function<Value()> work);
  Value submitPreemptible(
      std::function<RunSliceResult(const std::shared_ptr<TaskObject>&, size_t)> run_slice);
  size_t quantum_budget() const { return quantum_budget_; }
  void set_quantum_budget(size_t budget);

  static bool in_worker_thread();

 private:
  static void* worker_entry(void* self);
  void workerLoop();
  void finishTask(const std::shared_ptr<ScheduledTask>& task, const Value& value, TaskStatus status);
  void failTask(const std::shared_ptr<ScheduledTask>& task, TaskStatus status);
  void enqueueTask(std::shared_ptr<ScheduledTask> task);

  size_t num_workers_{0};
  std::vector<pthread_t> workers_;
  std::mutex mu_;
  std::condition_variable cv_;
  std::queue<std::shared_ptr<ScheduledTask>> queue_;
  bool stop_{false};
  std::atomic<size_t> quantum_budget_{20000};

  thread_local static bool tls_in_worker_;
};
