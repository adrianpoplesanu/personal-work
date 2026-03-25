#pragma once

#include "object.h"

#include <memory>
#include <string>
#include <unordered_map>

const std::unordered_map<std::string, std::shared_ptr<BuiltinObject>>& builtinMap();
