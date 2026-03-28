#include "builtins.h"

#include <iostream>
#include <stdexcept>

namespace {

Value builtin_len(const std::vector<Value>& args) {
  if (args.size() != 1) {
    throw std::runtime_error("len() expects 1 argument, got " + std::to_string(args.size()));
  }
  if (args[0].kind == Value::Kind::String) {
    return Value::makeInt(static_cast<int64_t>(args[0].string_val.size()));
  }
  if (args[0].kind == Value::Kind::Array) {
    return Value::makeInt(static_cast<int64_t>(args[0].elements->size()));
  }
  throw std::runtime_error("len() argument must be string or array");
}

Value builtin_puts(const std::vector<Value>& args) {
  for (const auto& a : args) {
    std::cout << a.inspect() << "\n";
  }
  return Value::null();
}

Value builtin_first(const std::vector<Value>& args) {
  if (args.size() != 1) {
    throw std::runtime_error("first() expects 1 argument");
  }
  if (args[0].kind != Value::Kind::Array) {
    throw std::runtime_error("first() requires an array");
  }
  const auto& el = *args[0].elements;
  if (el.empty()) return Value::null();
  return el[0];
}

Value builtin_last(const std::vector<Value>& args) {
  if (args.size() != 1) {
    throw std::runtime_error("last() expects 1 argument");
  }
  if (args[0].kind != Value::Kind::Array) {
    throw std::runtime_error("last() requires an array");
  }
  const auto& el = *args[0].elements;
  if (el.empty()) return Value::null();
  return el.back();
}

Value builtin_rest(const std::vector<Value>& args) {
  if (args.size() != 1) {
    throw std::runtime_error("rest() expects 1 argument");
  }
  if (args[0].kind != Value::Kind::Array) {
    throw std::runtime_error("rest() requires an array");
  }
  const auto& el = *args[0].elements;
  if (el.empty()) return Value::null();
  auto out = std::make_shared<std::vector<Value>>(el.begin() + 1, el.end());
  return Value::makeArray(out);
}

Value builtin_push(const std::vector<Value>& args) {
  if (args.size() != 2) {
    throw std::runtime_error("push() expects 2 arguments");
  }
  if (args[0].kind != Value::Kind::Array) {
    throw std::runtime_error("push() first argument must be an array");
  }
  auto copy = std::make_shared<std::vector<Value>>(*args[0].elements);
  copy->push_back(args[1]);
  return Value::makeArray(copy);
}

Value builtin_join(const std::vector<Value>& args) {
  if (args.size() != 1) {
    throw std::runtime_error("join() expects 1 argument, got " + std::to_string(args.size()));
  }
  if (args[0].kind != Value::Kind::Thread) {
    throw std::runtime_error("join() requires a thread");
  }
  auto handle = args[0].thread_handle;
  if (handle->joined.exchange(true)) {
    throw std::runtime_error("join() on already joined thread");
  }
  try {
    Value result = handle->future.get();
    if (handle->thread && handle->thread->joinable()) {
      handle->thread->join();
    }
    return result;
  } catch (...) {
    if (handle->thread && handle->thread->joinable()) {
      handle->thread->join();
    }
    throw;
  }
}

void add(std::unordered_map<std::string, std::shared_ptr<BuiltinObject>>& m, const char* name,
         Value (*fn)(const std::vector<Value>&)) {
  auto b = std::make_shared<BuiltinObject>();
  b->name = name;
  b->fn = fn;
  m[name] = b;
}

}  // namespace

const std::unordered_map<std::string, std::shared_ptr<BuiltinObject>>& builtinMap() {
  static std::unordered_map<std::string, std::shared_ptr<BuiltinObject>> m;
  static bool init = false;
  if (!init) {
    init = true;
    add(m, "len", builtin_len);
    add(m, "puts", builtin_puts);
    add(m, "first", builtin_first);
    add(m, "last", builtin_last);
    add(m, "rest", builtin_rest);
    add(m, "push", builtin_push);
    add(m, "join", builtin_join);
  }
  return m;
}
