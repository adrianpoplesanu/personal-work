#pragma once

#include "object.h"

#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

struct Environment {
  mutable std::mutex mu;
  std::unordered_map<std::string, Value> store;
  std::shared_ptr<Environment> outer;

  explicit Environment(std::shared_ptr<Environment> outer_env = nullptr);

  std::optional<Value> tryGet(const std::string& name) const;
  Value get(const std::string& name) const;
  void set(const std::string& name, const Value& val);
  bool assign(const std::string& name, const Value& val);
};
