#include "evaluator.h"

#include "builtins.h"
#include "scheduler.h"
#include "stack_thread.h"

#include <future>
#include <stdexcept>
#include <thread>
#include <utility>

namespace {

std::string toString(const Value& v) {
  if (v.kind == Value::Kind::String) return v.string_val;
  return v.inspect();
}

thread_local TaskExecutionContext* tls_task_ctx = nullptr;

Value applyInfixOp(TokenType op, const Value& left, const Value& right) {
  switch (op) {
    case TokenType::PLUS:
      if (left.kind == Value::Kind::Integer && right.kind == Value::Kind::Integer) {
        return Value::makeInt(left.integer + right.integer);
      }
      if (left.kind == Value::Kind::String && right.kind == Value::Kind::String) {
        return Value::makeString(left.string_val + right.string_val);
      }
      if (left.kind == Value::Kind::String) {
        return Value::makeString(left.string_val + toString(right));
      }
      if (right.kind == Value::Kind::String) {
        return Value::makeString(toString(left) + right.string_val);
      }
      throw std::runtime_error("unsupported operands for +");
    case TokenType::MINUS:
      if (left.kind != Value::Kind::Integer || right.kind != Value::Kind::Integer) {
        throw std::runtime_error("operands must be integers");
      }
      return Value::makeInt(left.integer - right.integer);
    case TokenType::ASTERISK:
      if (left.kind != Value::Kind::Integer || right.kind != Value::Kind::Integer) {
        throw std::runtime_error("operands must be integers");
      }
      return Value::makeInt(left.integer * right.integer);
    case TokenType::SLASH:
      if (left.kind != Value::Kind::Integer || right.kind != Value::Kind::Integer) {
        throw std::runtime_error("operands must be integers");
      }
      if (right.integer == 0) throw std::runtime_error("division by zero");
      return Value::makeInt(left.integer / right.integer);
    case TokenType::PERCENT:
      if (left.kind != Value::Kind::Integer || right.kind != Value::Kind::Integer) {
        throw std::runtime_error("operands must be integers");
      }
      if (right.integer == 0) throw std::runtime_error("division by zero");
      return Value::makeInt(left.integer % right.integer);
    case TokenType::LT:
      if (left.kind != Value::Kind::Integer || right.kind != Value::Kind::Integer) {
        throw std::runtime_error("operands must be integers");
      }
      return Value::makeBool(left.integer < right.integer);
    case TokenType::GT:
      if (left.kind != Value::Kind::Integer || right.kind != Value::Kind::Integer) {
        throw std::runtime_error("operands must be integers");
      }
      return Value::makeBool(left.integer > right.integer);
    case TokenType::LT_EQ:
      if (left.kind != Value::Kind::Integer || right.kind != Value::Kind::Integer) {
        throw std::runtime_error("operands must be integers");
      }
      return Value::makeBool(left.integer <= right.integer);
    case TokenType::GT_EQ:
      if (left.kind != Value::Kind::Integer || right.kind != Value::Kind::Integer) {
        throw std::runtime_error("operands must be integers");
      }
      return Value::makeBool(left.integer >= right.integer);
    case TokenType::EQ:
      return Value::makeBool(valueEquals(left, right));
    case TokenType::NOT_EQ:
      return Value::makeBool(!valueEquals(left, right));
    default:
      throw std::runtime_error("unknown infix operator");
  }
}

}  // namespace

bool inTaskExecutionContext() { return tls_task_ctx != nullptr; }

RunSliceResult runResumeSlice(const std::shared_ptr<TaskScheduler>& sched,
                              const std::shared_ptr<TaskObject>& handle, size_t budget,
                              const std::function<Value(const Value&)>& resume_cont, Value pending,
                              std::exception_ptr pending_error) {
  TaskExecutionContext ctx;
  ctx.task = handle;
  ctx.checkpoint_budget = budget;
  ctx.remaining_budget = budget;
  Evaluator eval(nullptr, sched);
  return eval.runWorkSlice(ctx, [&]() {
    if (pending_error) {
      std::rethrow_exception(pending_error);
    }
    return resume_cont(pending);
  });
}

Evaluator::Evaluator(Program* program, std::shared_ptr<TaskScheduler> scheduler)
    : program_(program), scheduler_(std::move(scheduler)) {}

void Evaluator::checkpoint(TaskExecutionContext* ctx) {
  if (ctx == nullptr) {
    ctx = tls_task_ctx;
  }
  if (ctx == nullptr) {
    return;
  }
  ctx->checkpoints++;
  if (ctx->task && ctx->task->cancel_requested.load()) {
    throw std::runtime_error("task cancelled");
  }
  if (ctx->remaining_budget > 0) {
    ctx->remaining_budget--;
  }
  if (ctx->remaining_budget == 0) {
    ctx->yield_requested = true;
    ctx->remaining_budget = ctx->checkpoint_budget;
    std::this_thread::yield();
  }
}

Value Evaluator::eval(std::shared_ptr<Environment> env) { return evalProgramBlock(env); }

Value Evaluator::evalProgramBlock(const std::shared_ptr<Environment>& env) {
  EvalResult last{Value::null(), false};
  for (auto& stmt : program_->statements) {
    last = evalStatement(stmt.get(), env);
    if (last.returned) {
      return last.value;
    }
  }
  return last.value;
}

EvalResult Evaluator::evalStatement(Statement* stmt, const std::shared_ptr<Environment>& env) {
  checkpoint(nullptr);
  if (auto* ls = dynamic_cast<LetStatementStmt*>(stmt)) {
    Value v = Value::null();
    if (ls->value) {
      try {
        v = evalExpression(ls->value.get(), env);
      } catch (SuspendRequest& sr) {
        auto prev = std::move(sr.resume_cont);
        auto env_c = env;
        std::string name = ls->name.value;
        sr.resume_cont = [prev = std::move(prev), env_c, name](const Value& rv) {
          Value val = prev(rv);
          env_c->set(name, val);
          return Value::null();
        };
        throw;
      }
    }
    env->set(ls->name.value, v);
    return {Value::null(), false};
  }
  if (auto* rs = dynamic_cast<ReturnStatementStmt*>(stmt)) {
    Value v = Value::null();
    if (rs->return_value) {
      try {
        v = evalExpression(rs->return_value.get(), env);
      } catch (SuspendRequest& sr) {
        sr.done_after = true;
        throw;
      }
    }
    return {v, true};
  }
  if (auto* es = dynamic_cast<ExpressionStatementStmt*>(stmt)) {
    Value v = evalExpression(es->expression.get(), env);
    return {v, false};
  }
  if (auto* bs = dynamic_cast<BlockStatementStmt*>(stmt)) {
    return evalBlockStatement(static_cast<BlockStatement*>(bs), env);
  }
  if (auto* fs = dynamic_cast<ForStatementStmt*>(stmt)) {
    auto loop_env = std::make_shared<Environment>(env);
    if (fs->init) {
      EvalResult init_res = evalStatement(fs->init.get(), loop_env);
      if (init_res.returned) {
        return init_res;
      }
    }
    while (true) {
      checkpoint(nullptr);
      if (fs->condition) {
        if (!isTruthy(evalExpression(fs->condition.get(), loop_env))) {
          break;
        }
      }
      EvalResult body_res = evalBlockStatement(fs->body.get(), loop_env);
      if (body_res.returned) {
        return body_res;
      }
      if (fs->update) {
        evalExpression(fs->update.get(), loop_env);
      }
    }
    return {Value::null(), false};
  }
  if (auto* cs = dynamic_cast<ClassStatementStmt*>(stmt)) {
    auto klass = std::make_shared<ClassObject>();
    klass->name = cs->name.value;
    for (const auto& m : cs->methods) {
      auto fn = std::make_shared<FunctionObject>();
      fn->name = m.name.value;
      for (const auto& p : m.parameters) {
        fn->parameters.push_back(p.value);
      }
      fn->body = m.body.get();
      fn->env = env;
      klass->methods[m.name.value] = fn;
    }
    env->set(cs->name.value, Value::makeClass(klass));
    return {Value::null(), false};
  }
  throw std::runtime_error("unknown statement type");
}

EvalResult Evaluator::evalBlockStatement(BlockStatement* block, const std::shared_ptr<Environment>& env) {
  EvalResult last{Value::null(), false};
  for (size_t i = 0; i < block->statements.size(); ++i) {
    try {
      last = evalStatement(block->statements[i].get(), env);
    } catch (SuspendRequest& sr) {
      auto prev = std::move(sr.resume_cont);
      bool done_after = sr.done_after;
      sr.done_after = false;
      auto env_c = env;
      BlockStatement* blk = block;
      size_t idx = i;
      Program* prog = program_;
      auto sched = scheduler_;
      sr.resume_cont = [prev = std::move(prev), done_after, env_c, blk, idx, prog,
                        sched](const Value& rv) {
        Evaluator eval(prog, sched);
        Value cur = prev(rv);
        if (done_after) {
          return cur;
        }
        for (size_t j = idx + 1; j < blk->statements.size(); ++j) {
          try {
            EvalResult r = eval.evalStatement(blk->statements[j].get(), env_c);
            if (r.returned) {
              return r.value;
            }
            cur = r.value;
          } catch (SuspendRequest& sr2) {
            auto prev2 = std::move(sr2.resume_cont);
            bool done2 = sr2.done_after;
            sr2.done_after = false;
            auto env2 = env_c;
            BlockStatement* blk2 = blk;
            size_t idx2 = j;
            Program* prog2 = prog;
            auto sched2 = sched;
            sr2.resume_cont = [prev2 = std::move(prev2), done2, env2, blk2, idx2, prog2,
                               sched2](const Value& rv2) {
              Evaluator eval2(prog2, sched2);
              Value cur2 = prev2(rv2);
              if (done2) {
                return cur2;
              }
              for (size_t k = idx2 + 1; k < blk2->statements.size(); ++k) {
                EvalResult r2 = eval2.evalStatement(blk2->statements[k].get(), env2);
                if (r2.returned) {
                  return r2.value;
                }
                cur2 = r2.value;
              }
              return cur2;
            };
            throw;
          }
        }
        return cur;
      };
      throw;
    }
    if (last.returned) {
      return last;
    }
  }
  return last;
}

Value Evaluator::evalExpression(Expression* expr, const std::shared_ptr<Environment>& env) {
  checkpoint(nullptr);
  if (auto* ie = dynamic_cast<IntegerLiteralExpr*>(expr)) {
    return Value::makeInt(ie->value);
  }
  if (auto* se = dynamic_cast<StringLiteralExpr*>(expr)) {
    return Value::makeString(se->value);
  }
  if (auto* be = dynamic_cast<BooleanLiteralExpr*>(expr)) {
    return Value::makeBool(be->value);
  }
  if (dynamic_cast<ThisExpressionExpr*>(expr)) {
    if (auto th = env->tryGet("this")) {
      return *th;
    }
    throw std::runtime_error("'this' used outside of a method");
  }
  if (auto* id = dynamic_cast<IdentifierExpr*>(expr)) {
    if (auto v = env->tryGet(id->value)) {
      return *v;
    }
    const auto& builtins = builtinMap();
    auto bit = builtins.find(id->value);
    if (bit != builtins.end()) {
      return Value::makeBuiltin(bit->second);
    }
    throw std::runtime_error("identifier not found: " + id->value);
  }
  if (auto* pe = dynamic_cast<PrefixExpressionExpr*>(expr)) {
    Value right = evalExpression(pe->right.get(), env);
    if (pe->op.type == TokenType::BANG) {
      return Value::makeBool(!isTruthy(right));
    }
    if (pe->op.type == TokenType::MINUS) {
      if (right.kind != Value::Kind::Integer) {
        throw std::runtime_error("- only defined for integers");
      }
      return Value::makeInt(-right.integer);
    }
    throw std::runtime_error("unknown prefix operator");
  }
  if (auto* inf = dynamic_cast<InfixExpressionExpr*>(expr)) {
    Value left;
    try {
      left = evalExpression(inf->left.get(), env);
    } catch (SuspendRequest& sr) {
      auto prev = std::move(sr.resume_cont);
      Expression* right_expr = inf->right.get();
      TokenType op = inf->op.type;
      auto env_c = env;
      Program* prog = program_;
      auto sched = scheduler_;
      sr.resume_cont = [prev = std::move(prev), right_expr, op, env_c, prog,
                        sched](const Value& rv) {
        Evaluator eval(prog, sched);
        Value left_v = prev(rv);
        try {
          Value right_v = eval.evalExpression(right_expr, env_c);
          return applyInfixOp(op, left_v, right_v);
        } catch (SuspendRequest& sr2) {
          auto prev2 = std::move(sr2.resume_cont);
          Value left_c = left_v;
          TokenType op_c = op;
          sr2.resume_cont = [prev2 = std::move(prev2), left_c, op_c](const Value& rv2) {
            return applyInfixOp(op_c, left_c, prev2(rv2));
          };
          throw;
        }
      };
      throw;
    }
    if (inf->op.type == TokenType::PLUS) {
      Value right;
      try {
        right = evalExpression(inf->right.get(), env);
      } catch (SuspendRequest& sr) {
        auto prev = std::move(sr.resume_cont);
        Value left_c = left;
        TokenType op = TokenType::PLUS;
        sr.resume_cont = [prev = std::move(prev), left_c, op](const Value& rv) {
          return applyInfixOp(op, left_c, prev(rv));
        };
        throw;
      }
      return applyInfixOp(TokenType::PLUS, left, right);
    }
    Value right;
    try {
      right = evalExpression(inf->right.get(), env);
    } catch (SuspendRequest& sr) {
      auto prev = std::move(sr.resume_cont);
      Value left_c = left;
      TokenType op = inf->op.type;
      sr.resume_cont = [prev = std::move(prev), left_c, op](const Value& rv) {
        return applyInfixOp(op, left_c, prev(rv));
      };
      throw;
    }
    return applyInfixOp(inf->op.type, left, right);
  }
  if (auto* ie = dynamic_cast<IfExpressionExpr*>(expr)) {
    Value cond = evalExpression(ie->condition.get(), env);
    if (isTruthy(cond)) {
      return evalBlockStatement(ie->consequence.get(), env).value;
    }
    if (ie->alternative) {
      return evalBlockStatement(ie->alternative.get(), env).value;
    }
    return Value::null();
  }
  if (auto* al = dynamic_cast<ArrayLiteralExpr*>(expr)) {
    auto vec = std::make_shared<std::vector<Value>>();
    vec->reserve(al->elements.size());
    for (auto& e : al->elements) {
      vec->push_back(evalExpression(e.get(), env));
    }
    return Value::makeArray(vec);
  }
  if (auto* idxe = dynamic_cast<IndexExpressionExpr*>(expr)) {
    Value left = evalExpression(idxe->left.get(), env);
    Value index = evalExpression(idxe->index.get(), env);
    if (left.kind != Value::Kind::Array) {
      throw std::runtime_error("only arrays support indexing");
    }
    if (index.kind != Value::Kind::Integer) {
      throw std::runtime_error("array index must be integer");
    }
    const auto& el = *left.elements;
    int64_t i = index.integer;
    if (i < 0 || static_cast<size_t>(i) >= el.size()) {
      return Value::null();
    }
    return el[static_cast<size_t>(i)];
  }
  if (auto* fl = dynamic_cast<FunctionLiteralExpr*>(expr)) {
    auto fn = std::make_shared<FunctionObject>();
    fn->name = "lambda";
    for (const auto& p : fl->parameters) {
      fn->parameters.push_back(p.value);
    }
    fn->body = fl->body.get();
    fn->env = env;
    fn->is_async = fl->is_async;
    return Value::makeFunction(fn);
  }
  if (auto* aw = dynamic_cast<AwaitExpressionExpr*>(expr)) {
    Value inner = evalExpression(aw->operand.get(), env);
    return joinTaskValue(inner);
  }
  if (auto* se = dynamic_cast<SpawnExpressionExpr*>(expr)) {
    Value callee = evalExpression(se->function.get(), env);
    std::vector<Value> args;
    for (auto& a : se->arguments) {
      args.push_back(evalExpression(a.get(), env));
    }
    return spawnCall(callee, args);
  }
  if (auto* ce = dynamic_cast<CallExpressionExpr*>(expr)) {
    Value callee = evalExpression(ce->function.get(), env);
    std::vector<Value> args;
    args.reserve(ce->arguments.size());
    for (size_t i = 0; i < ce->arguments.size(); ++i) {
      try {
        args.push_back(evalExpression(ce->arguments[i].get(), env));
      } catch (SuspendRequest& sr) {
        auto prev = std::move(sr.resume_cont);
        Value callee_c = callee;
        std::vector<Value> args_so_far = args;
        auto* call = ce;
        size_t arg_i = i;
        auto env_c = env;
        Program* prog = program_;
        auto sched = scheduler_;
        sr.resume_cont = [prev = std::move(prev), callee_c, args_so_far = std::move(args_so_far), call,
                          arg_i, env_c, prog, sched](const Value& rv) mutable {
          Evaluator eval(prog, sched);
          args_so_far.push_back(prev(rv));
          for (size_t j = arg_i + 1; j < call->arguments.size(); ++j) {
            try {
              args_so_far.push_back(eval.evalExpression(call->arguments[j].get(), env_c));
            } catch (SuspendRequest& sr2) {
              auto prev2 = std::move(sr2.resume_cont);
              Value callee2 = callee_c;
              std::vector<Value> args2 = args_so_far;
              auto* call2 = call;
              size_t arg_j = j;
              auto env2 = env_c;
              Program* prog2 = prog;
              auto sched2 = sched;
              sr2.resume_cont = [prev2 = std::move(prev2), callee2, args2 = std::move(args2), call2,
                                 arg_j, env2, prog2, sched2](const Value& rv2) mutable {
                Evaluator eval2(prog2, sched2);
                args2.push_back(prev2(rv2));
                for (size_t k = arg_j + 1; k < call2->arguments.size(); ++k) {
                  args2.push_back(eval2.evalExpression(call2->arguments[k].get(), env2));
                }
                return eval2.callValue(callee2, args2);
              };
              throw;
            }
          }
          return eval.callValue(callee_c, args_so_far);
        };
        throw;
      }
    }
    return callValue(callee, args);
  }
  if (auto* ne = dynamic_cast<NewExpressionExpr*>(expr)) {
    auto clsOpt = env->tryGet(ne->class_name.value);
    if (!clsOpt) {
      throw std::runtime_error("identifier not found: " + ne->class_name.value);
    }
    Value clsVal = *clsOpt;
    if (clsVal.kind != Value::Kind::Class) {
      throw std::runtime_error("new requires a class");
    }
    auto inst = std::make_shared<InstanceObject>();
    inst->klass = clsVal.klass;
    auto it = clsVal.klass->methods.find("init");
    if (it != clsVal.klass->methods.end()) {
      std::vector<Value> args;
      for (auto& a : ne->arguments) {
        args.push_back(evalExpression(a.get(), env));
      }
      applyFunction(it->second, args, inst);
    }
    return Value::makeInstance(inst);
  }
  if (auto* me = dynamic_cast<MemberExpressionExpr*>(expr)) {
    Value obj = evalExpression(me->object.get(), env);
    if (obj.kind != Value::Kind::Instance) {
      throw std::runtime_error("only instances have members");
    }
    const std::string& name = me->member.value;
    auto it = obj.instance->fields.find(name);
    if (it != obj.instance->fields.end()) {
      return it->second;
    }
    auto mit = obj.instance->klass->methods.find(name);
    if (mit != obj.instance->klass->methods.end()) {
      auto bm = std::make_shared<BoundMethodObject>();
      bm->method = mit->second;
      bm->instance = obj.instance;
      return Value::makeBoundMethod(bm);
    }
    throw std::runtime_error("unknown member: " + name);
  }
  if (auto* ae = dynamic_cast<AssignExpressionExpr*>(expr)) {
    Value rhs = evalExpression(ae->value.get(), env);
    if (auto* id = dynamic_cast<IdentifierExpr*>(ae->left.get())) {
      if (!env->assign(id->value, rhs)) {
        env->set(id->value, rhs);
      }
      return rhs;
    }
    if (auto* mem = dynamic_cast<MemberExpressionExpr*>(ae->left.get())) {
      Value obj = evalExpression(mem->object.get(), env);
      if (obj.kind != Value::Kind::Instance) {
        throw std::runtime_error("only instances have fields");
      }
      obj.instance->fields[mem->member.value] = rhs;
      return rhs;
    }
    if (auto* ix = dynamic_cast<IndexExpressionExpr*>(ae->left.get())) {
      Value arr = evalExpression(ix->left.get(), env);
      Value index = evalExpression(ix->index.get(), env);
      if (arr.kind != Value::Kind::Array) {
        throw std::runtime_error("indexed assignment requires an array");
      }
      if (index.kind != Value::Kind::Integer) {
        throw std::runtime_error("array index must be integer");
      }
      int64_t i = index.integer;
      if (i < 0 || static_cast<size_t>(i) >= arr.elements->size()) {
        throw std::runtime_error("array index out of bounds in assignment");
      }
      (*arr.elements)[static_cast<size_t>(i)] = rhs;
      return rhs;
    }
    throw std::runtime_error("invalid assignment target");
  }
  throw std::runtime_error("unknown expression type");
}

Value Evaluator::applyFunction(const std::shared_ptr<FunctionObject>& fn, const std::vector<Value>& args,
                               const std::shared_ptr<InstanceObject>& this_binding) {
  checkpoint(nullptr);
  auto fnEnv = std::make_shared<Environment>(fn->env);
  for (size_t i = 0; i < fn->parameters.size(); ++i) {
    Value arg = i < args.size() ? args[i] : Value::null();
    fnEnv->set(fn->parameters[i], arg);
  }
  if (this_binding) {
    fnEnv->set("this", Value::makeInstance(this_binding));
  }
  Evaluator inner(program_, scheduler_);
  try {
    EvalResult r = inner.evalBlockStatement(fn->body, fnEnv);
    return r.value;
  } catch (SuspendRequest& sr) {
    // Block wrapper already builds a Value-producing continuation.
    throw;
  }
}

RunSliceResult Evaluator::runCallableSlice(TaskExecutionContext& ctx, const Value& callee,
                                           const std::vector<Value>& args) {
  return runWorkSlice(ctx, [this, callee, args]() { return callValue(callee, args); });
}

RunSliceResult Evaluator::runWorkSlice(TaskExecutionContext& ctx, const std::function<Value()>& work) {
  if (ctx.checkpoint_budget == 0) {
    ctx.checkpoint_budget = 1;
  }
  if (ctx.remaining_budget == 0) {
    ctx.remaining_budget = ctx.checkpoint_budget;
  }

  TaskExecutionContext* prev = tls_task_ctx;
  tls_task_ctx = &ctx;
  RunSliceResult result;
  try {
    Value computed = work();
    if (ctx.yield_requested) {
      result.status = RunSliceResult::Status::Yielded;
      result.continuation = [computed](const std::shared_ptr<TaskObject>&, size_t) mutable {
        RunSliceResult resumed;
        resumed.status = RunSliceResult::Status::Completed;
        resumed.value = computed;
        return resumed;
      };
    } else {
      result.status = RunSliceResult::Status::Completed;
      result.value = computed;
    }
    result.checkpoints = ctx.checkpoints;
  } catch (SuspendRequest& sr) {
    result.status = RunSliceResult::Status::Suspended;
    result.suspend_kind = sr.kind;
    result.wake_at = sr.wake_at;
    result.join_target = sr.join_target;
    result.resume_continuation = std::move(sr.resume_cont);
    if (!result.resume_continuation) {
      result.resume_continuation = [](const Value& v) { return v; };
    }
    result.checkpoints = ctx.checkpoints;
    tls_task_ctx = prev;
    return result;
  } catch (...) {
    tls_task_ctx = prev;
    throw;
  }
  tls_task_ctx = prev;
  return result;
}

namespace {

struct SpawnPayload {
  Program* prog{nullptr};
  std::shared_ptr<std::promise<Value>> prom;
  Value callee;
  std::vector<Value> args;
};

void* spawn_thread_main(void* p) {
  auto* pl = static_cast<SpawnPayload*>(p);
  try {
    Evaluator eval(pl->prog, nullptr);
    Value v = eval.callValue(pl->callee, pl->args);
    pl->prom->set_value(std::move(v));
  } catch (...) {
    try {
      pl->prom->set_exception(std::current_exception());
    } catch (...) {
    }
  }
  delete pl;
  return nullptr;
}

}  // namespace

Value Evaluator::spawnCall(const Value& callee, const std::vector<Value>& args) {
  Program* prog = program_;
  Value callee_copy = callee;
  std::vector<Value> args_copy = args;
  auto sched = scheduler_;

  if (sched) {
    auto task = sched->submitPreemptible(
        [prog, sched, callee_copy, args_copy](const std::shared_ptr<TaskObject>& handle, size_t budget) mutable {
      TaskExecutionContext ctx;
      ctx.task = handle;
      ctx.checkpoint_budget = budget;
      ctx.remaining_budget = budget;
      Evaluator eval(prog, sched);
      return eval.runCallableSlice(ctx, callee_copy, args_copy);
    });
    return task;
  }

  auto handle = std::make_shared<TaskObject>();
  auto prom = std::make_shared<std::promise<Value>>();
  handle->future = prom->get_future();
  auto pl = new SpawnPayload{prog, std::move(prom), std::move(callee_copy), std::move(args_copy)};
  pthread_t tid{};
  constexpr size_t kStack = 8u * 1024u * 1024u;
  if (!start_pthread_with_stack(kStack, spawn_thread_main, pl, &tid)) {
    delete pl;
    throw std::runtime_error("failed to spawn thread");
  }
  handle->overflow_pthread = tid;
  handle->has_overflow_pthread = true;
  return Value::makeTask(handle);
}

Value Evaluator::callValue(const Value& callee, const std::vector<Value>& args) {
  if (callee.kind == Value::Kind::Builtin) {
    return callee.builtin->fn(args);
  }
  if (callee.kind == Value::Kind::Function) {
    if (callee.fn->is_async) {
      if (!scheduler_) {
        throw std::runtime_error("async function requires a scheduler (pass TaskScheduler from main)");
      }
      auto fn = callee.fn;
      return scheduler_->submitPreemptible(
          [this, fn, args](const std::shared_ptr<TaskObject>& handle, size_t budget) mutable {
        TaskExecutionContext ctx;
        ctx.task = handle;
        ctx.checkpoint_budget = budget;
        ctx.remaining_budget = budget;
        Evaluator eval(program_, scheduler_);
        return eval.runWorkSlice(ctx, [&eval, fn, args]() { return eval.applyFunction(fn, args, nullptr); });
      });
    }
    return applyFunction(callee.fn, args, nullptr);
  }
  if (callee.kind == Value::Kind::BoundMethod) {
    if (callee.bound_method->method->is_async) {
      if (!scheduler_) {
        throw std::runtime_error("async method requires a scheduler (pass TaskScheduler from main)");
      }
      auto bm = callee.bound_method;
      return scheduler_->submitPreemptible(
          [this, bm, args](const std::shared_ptr<TaskObject>& handle, size_t budget) mutable {
        TaskExecutionContext ctx;
        ctx.task = handle;
        ctx.checkpoint_budget = budget;
        ctx.remaining_budget = budget;
        Evaluator eval(program_, scheduler_);
        return eval.runWorkSlice(ctx, [&eval, bm, args]() { return eval.applyFunction(bm->method, args, bm->instance); });
      });
    }
    return applyFunction(callee.bound_method->method, args, callee.bound_method->instance);
  }
  if (callee.kind == Value::Kind::Class) {
    auto inst = std::make_shared<InstanceObject>();
    inst->klass = callee.klass;
    auto it = callee.klass->methods.find("init");
    if (it != callee.klass->methods.end()) {
      applyFunction(it->second, args, inst);
    }
    return Value::makeInstance(inst);
  }
  throw std::runtime_error("not a function or class: " + callee.inspect());
}
