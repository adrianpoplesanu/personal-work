#include "environment.h"

#include <stdexcept>

Environment::Environment(std::shared_ptr<Environment> outer_env) : outer(std::move(outer_env)) {}

std::optional<Value> Environment::tryGet(const std::string& name) const {
  auto it = store.find(name);
  if (it != store.end()) {
    return it->second;
  }
  if (outer) {
    return outer->tryGet(name);
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

void Environment::set(const std::string& name, const Value& val) { store[name] = val; }

bool Environment::assign(const std::string& name, const Value& val) {
  auto it = store.find(name);
  if (it != store.end()) {
    it->second = val;
    return true;
  }
  if (outer) {
    return outer->assign(name, val);
  }
  return false;
}
