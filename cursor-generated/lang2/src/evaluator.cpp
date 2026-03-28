#include "evaluator.h"

#include "builtins.h"

#include <future>
#include <stdexcept>
#include <thread>

namespace {

std::string toString(const Value& v) {
  if (v.kind == Value::Kind::String) return v.string_val;
  return v.inspect();
}

}  // namespace

Evaluator::Evaluator(Program* program) : program_(program) {}

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
  if (auto* ls = dynamic_cast<LetStatementStmt*>(stmt)) {
    Value v = Value::null();
    if (ls->value) {
      v = evalExpression(ls->value.get(), env);
    }
    env->set(ls->name.value, v);
    return {Value::null(), false};
  }
  if (auto* rs = dynamic_cast<ReturnStatementStmt*>(stmt)) {
    Value v = Value::null();
    if (rs->return_value) {
      v = evalExpression(rs->return_value.get(), env);
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
  for (auto& st : block->statements) {
    last = evalStatement(st.get(), env);
    if (last.returned) {
      return last;
    }
  }
  return last;
}

Value Evaluator::evalExpression(Expression* expr, const std::shared_ptr<Environment>& env) {
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
    Value left = evalExpression(inf->left.get(), env);
    if (inf->op.type == TokenType::PLUS) {
      Value right = evalExpression(inf->right.get(), env);
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
    }
    Value right = evalExpression(inf->right.get(), env);
    switch (inf->op.type) {
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
        break;
    }
    throw std::runtime_error("unknown infix operator");
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
    return Value::makeFunction(fn);
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
    for (auto& a : ce->arguments) {
      args.push_back(evalExpression(a.get(), env));
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
  auto fnEnv = std::make_shared<Environment>(fn->env);
  for (size_t i = 0; i < fn->parameters.size(); ++i) {
    Value arg = i < args.size() ? args[i] : Value::null();
    fnEnv->set(fn->parameters[i], arg);
  }
  if (this_binding) {
    fnEnv->set("this", Value::makeInstance(this_binding));
  }
  Evaluator inner(program_);
  EvalResult r = inner.evalBlockStatement(fn->body, fnEnv);
  return r.value;
}

Value Evaluator::spawnCall(const Value& callee, const std::vector<Value>& args) {
  auto handle = std::make_shared<ThreadObject>();
  auto prom = std::make_shared<std::promise<Value>>();
  handle->future = prom->get_future();
  Program* prog = program_;
  Value callee_copy = callee;
  std::vector<Value> args_copy = args;
  handle->thread = std::make_unique<std::thread>([prog, prom, callee_copy, args_copy]() {
    try {
      Evaluator eval(prog);
      Value v = eval.callValue(callee_copy, args_copy);
      prom->set_value(std::move(v));
    } catch (...) {
      try {
        prom->set_exception(std::current_exception());
      } catch (...) {
      }
    }
  });
  return Value::makeThread(handle);
}

Value Evaluator::callValue(const Value& callee, const std::vector<Value>& args) {
  if (callee.kind == Value::Kind::Builtin) {
    return callee.builtin->fn(args);
  }
  if (callee.kind == Value::Kind::Function) {
    return applyFunction(callee.fn, args, nullptr);
  }
  if (callee.kind == Value::Kind::BoundMethod) {
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
