#pragma once

#include "ast.h"
#include "environment.h"
#include "object.h"
#include "scheduler.h"

#include <memory>

struct EvalResult {
  Value value{Value::null()};
  bool returned{false};
};

class TaskScheduler;

struct TaskExecutionContext {
  std::shared_ptr<TaskObject> task;
  size_t checkpoint_budget{0};
  size_t remaining_budget{0};
  bool yield_requested{false};
  uint64_t checkpoints{0};
};

class Evaluator {
 public:
  explicit Evaluator(Program* program, std::shared_ptr<TaskScheduler> scheduler = nullptr);

  Value eval(std::shared_ptr<Environment> env);

  Value callValue(const Value& callee, const std::vector<Value>& args);
  RunSliceResult runCallableSlice(TaskExecutionContext& ctx, const Value& callee, const std::vector<Value>& args);
  RunSliceResult runWorkSlice(TaskExecutionContext& ctx, const std::function<Value()>& work);

 private:
  void checkpoint(TaskExecutionContext* ctx);
  EvalResult evalStatement(Statement* stmt, const std::shared_ptr<Environment>& env);
  EvalResult evalBlockStatement(BlockStatement* block, const std::shared_ptr<Environment>& env);
  Value evalExpression(Expression* expr, const std::shared_ptr<Environment>& env);
  Value evalProgramBlock(const std::shared_ptr<Environment>& env);

  Value applyFunction(const std::shared_ptr<FunctionObject>& fn, const std::vector<Value>& args,
                      const std::shared_ptr<InstanceObject>& this_binding);
  Value spawnCall(const Value& callee, const std::vector<Value>& args);

  Program* program_;
  std::shared_ptr<TaskScheduler> scheduler_;
};
