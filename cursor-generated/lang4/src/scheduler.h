#pragma once

#include "object.h"

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <exception>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <pthread.h>
#include <queue>
#include <vector>

struct SuspendRequest {
  enum class Kind { Delay, Join };

  Kind kind{Kind::Delay};
  std::chrono::steady_clock::time_point wake_at{};
  std::shared_ptr<TaskObject> join_target;
  // Maps the resume value at the suspend site to the remaining computation result.
  std::function<Value(const Value&)> resume_cont;
  // If true, the suspended statement was a return; block wrappers should stop after resume.
  bool done_after{false};

  const char* what() const noexcept { return "task suspended"; }
};

struct RunSliceResult {
  enum class Status { Completed, Yielded, Suspended };
  Status status{Status::Completed};
  Value value{Value::null()};
  std::function<RunSliceResult(const std::shared_ptr<TaskObject>&, size_t)> continuation;
  std::function<Value(const Value&)> resume_continuation;
  SuspendRequest::Kind suspend_kind{SuspendRequest::Kind::Delay};
  std::chrono::steady_clock::time_point wake_at{};
  std::shared_ptr<TaskObject> join_target;
  uint64_t checkpoints{0};
};

struct ScheduledTask : public std::enable_shared_from_this<ScheduledTask> {
  std::shared_ptr<TaskObject> handle;
  std::shared_ptr<std::promise<Value>> promise;
  std::function<RunSliceResult(const std::shared_ptr<TaskObject>&, size_t)> run_slice;
  Value pending_resume{Value::null()};
  std::exception_ptr pending_error;
  bool has_pending_resume{false};
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

  void requestCancel(const std::shared_ptr<TaskObject>& handle);

  static bool in_worker_thread();

 private:
  struct DelayItem {
    std::chrono::steady_clock::time_point wake_at;
    uint64_t generation{0};
    std::shared_ptr<ScheduledTask> task;
  };

  struct DelayItemCompare {
    bool operator()(const DelayItem& a, const DelayItem& b) const {
      return a.wake_at > b.wake_at;
    }
  };

  static void* worker_entry(void* self);
  static void* timer_entry(void* self);
  void workerLoop();
  void timerLoop();
  void finishTask(const std::shared_ptr<ScheduledTask>& task, const Value& value, TaskStatus status);
  void failTask(const std::shared_ptr<ScheduledTask>& task, TaskStatus status);
  void enqueueTask(std::shared_ptr<ScheduledTask> task);
  void parkOnDelay(std::shared_ptr<ScheduledTask> task, std::chrono::steady_clock::time_point wake_at);
  void parkOnJoin(std::shared_ptr<ScheduledTask> task, const std::shared_ptr<TaskObject>& target);
  void armResumeSlice(std::shared_ptr<ScheduledTask> task,
                      std::function<Value(const Value&)> resume_cont);
  bool cancelParkedLocked(const std::shared_ptr<TaskObject>& handle,
                          std::vector<std::shared_ptr<ScheduledTask>>* out_fail);

  size_t num_workers_{0};
  std::vector<pthread_t> workers_;
  pthread_t timer_thread_{};
  bool timer_started_{false};

  std::mutex mu_;
  std::condition_variable cv_;
  std::queue<std::shared_ptr<ScheduledTask>> queue_;
  bool stop_{false};
  std::atomic<size_t> quantum_budget_{20000};

  std::mutex delay_mu_;
  std::condition_variable delay_cv_;
  std::priority_queue<DelayItem, std::vector<DelayItem>, DelayItemCompare> delay_queue_;

  thread_local static bool tls_in_worker_;
};
