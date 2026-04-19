#include "environment.h"

#include <stdexcept>

Environment::Environment(std::shared_ptr<Environment> outer_env) : outer(std::move(outer_env)) {}

std::optional<Value> Environment::tryGet(const std::string& name) const {
  std::shared_ptr<Environment> outer_copy;
  {
    std::lock_guard<std::mutex> lk(mu);
    auto it = store.find(name);
    if (it != store.end()) {
      return it->second;
    }
    outer_copy = outer;
  }
  if (outer_copy) {
    return outer_copy->tryGet(name);
  }
  return std::nullopt;
}

Value Environment::get(const std::string& name) const {
  auto v = tryGet(name);
  if (v) {
    return *v;
  }
  throw std::runtime_error("identifier not found: " + name);
}

void Environment::set(const std::string& name, const Value& val) {
  std::lock_guard<std::mutex> lk(mu);
  store[name] = val;
}

bool Environment::assign(const std::string& name, const Value& val) {
  std::shared_ptr<Environment> outer_copy;
  {
    std::lock_guard<std::mutex> lk(mu);
    auto it = store.find(name);
    if (it != store.end()) {
      it->second = val;
      return true;
    }
    outer_copy = outer;
  }
  if (outer_copy) {
    return outer_copy->assign(name, val);
  }
  return false;
}
