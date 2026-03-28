#pragma once

#include "ast.h"
#include "environment.h"
#include "object.h"

#include <memory>

struct EvalResult {
  Value value{Value::null()};
  bool returned{false};
};

class Evaluator {
 public:
  explicit Evaluator(Program* program);

  Value eval(std::shared_ptr<Environment> env);

 private:
  EvalResult evalStatement(Statement* stmt, const std::shared_ptr<Environment>& env);
  EvalResult evalBlockStatement(BlockStatement* block, const std::shared_ptr<Environment>& env);
  Value evalExpression(Expression* expr, const std::shared_ptr<Environment>& env);
  Value evalProgramBlock(const std::shared_ptr<Environment>& env);

  Value applyFunction(const std::shared_ptr<FunctionObject>& fn, const std::vector<Value>& args,
                      const std::shared_ptr<InstanceObject>& this_binding);
  Value callValue(const Value& callee, const std::vector<Value>& args);
  Value spawnCall(const Value& callee, const std::vector<Value>& args);

  Program* program_;
};
