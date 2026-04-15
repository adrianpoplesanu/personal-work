#pragma once

#include "ast.h"

#include <atomic>
#include <future>
#include <memory>
#include <ostream>
#include <string>
#include <pthread.h>
#include <chrono>
#include <unordered_map>
#include <vector>

struct Environment;
struct TaskObject;

enum class TaskStatus {
  Ready,
  Running,
  Yielded,
  Completed,
  Failed,
  Cancelled,
};

struct ContinuationState {
  // Placeholder for resumable interpreter frames as we evolve beyond checkpoints.
  uint64_t frame_id{0};
};

struct TaskMetrics {
  std::chrono::steady_clock::time_point submitted_at{std::chrono::steady_clock::now()};
  std::chrono::steady_clock::time_point first_started_at{};
  std::chrono::steady_clock::time_point completed_at{};
  uint64_t run_slices{0};
  uint64_t yield_count{0};
  uint64_t checkpoint_count{0};
};

struct FunctionObject {
  std::vector<std::string> parameters;
  BlockStatement* body{nullptr};
  std::shared_ptr<Environment> env;
  std::string name;
  bool is_async{false};
};

struct BuiltinObject;

struct ClassObject {
  std::string name;
  std::unordered_map<std::string, std::shared_ptr<FunctionObject>> methods;
};

struct InstanceObject;
struct BoundMethodObject;

struct Value {
  enum class Kind {
    Null,
    Integer,
    Boolean,
    String,
    Array,
    Function,
    Builtin,
    Class,
    Instance,
    BoundMethod,
    Task,
  } kind{Kind::Null};

  int64_t integer{0};
  bool boolean{false};
  std::string string_val;
  std::shared_ptr<std::vector<Value>> elements;
  std::shared_ptr<FunctionObject> fn;
  std::shared_ptr<BuiltinObject> builtin;
  std::shared_ptr<ClassObject> klass;
  std::shared_ptr<InstanceObject> instance;
  std::shared_ptr<BoundMethodObject> bound_method;
  std::shared_ptr<TaskObject> task_handle;

  static Value null();
  static Value makeInt(int64_t n);
  static Value makeBool(bool b);
  static Value makeString(std::string s);
  static Value makeArray(std::shared_ptr<std::vector<Value>> elems);
  static Value makeFunction(std::shared_ptr<FunctionObject> f);
  static Value makeBuiltin(std::shared_ptr<BuiltinObject> b);
  static Value makeClass(std::shared_ptr<ClassObject> c);
  static Value makeInstance(std::shared_ptr<InstanceObject> i);
  static Value makeBoundMethod(std::shared_ptr<BoundMethodObject> b);
  static Value makeTask(std::shared_ptr<TaskObject> t);

  std::string inspect() const;
};

struct TaskObject {
  std::future<Value> future;
  pthread_t overflow_pthread{};
  bool has_overflow_pthread{false};
  std::atomic<bool> joined{false};
  std::atomic<TaskStatus> status{TaskStatus::Ready};
  std::atomic<bool> cancel_requested{false};
  std::shared_ptr<ContinuationState> continuation;
  TaskMetrics metrics;
};

struct InstanceObject {
  std::shared_ptr<ClassObject> klass;
  std::unordered_map<std::string, Value> fields;
};

struct BuiltinObject {
  std::string name;
  Value (*fn)(const std::vector<Value>& args);
};

struct BoundMethodObject {
  std::shared_ptr<FunctionObject> method;
  std::shared_ptr<InstanceObject> instance;
};

bool isTruthy(const Value& v);
bool valueEquals(const Value& a, const Value& b);
const char* taskStatusName(TaskStatus status);

std::ostream& operator<<(std::ostream& os, const Value& v);
