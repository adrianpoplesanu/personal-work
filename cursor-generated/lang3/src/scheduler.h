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

class TaskScheduler : public std::enable_shared_from_this<TaskScheduler> {
 public:
  explicit TaskScheduler(size_t num_workers);
  ~TaskScheduler();

  Value submit(std::function<Value()> work);

  static bool in_worker_thread();

 private:
  static void* worker_entry(void* self);
  void workerLoop();

  size_t num_workers_{0};
  std::vector<pthread_t> workers_;
  std::mutex mu_;
  std::condition_variable cv_;
  std::queue<std::function<void()>> queue_;
  bool stop_{false};

  thread_local static bool tls_in_worker_;
};
