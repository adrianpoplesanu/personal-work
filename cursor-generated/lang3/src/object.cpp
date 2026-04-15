#include "object.h"

#include <sstream>

Value Value::null() {
  Value v;
  v.kind = Kind::Null;
  return v;
}

Value Value::makeInt(int64_t n) {
  Value v;
  v.kind = Kind::Integer;
  v.integer = n;
  return v;
}

Value Value::makeBool(bool b) {
  Value v;
  v.kind = Kind::Boolean;
  v.boolean = b;
  return v;
}

Value Value::makeString(std::string s) {
  Value v;
  v.kind = Kind::String;
  v.string_val = std::move(s);
  return v;
}

Value Value::makeArray(std::shared_ptr<std::vector<Value>> elems) {
  Value v;
  v.kind = Kind::Array;
  v.elements = std::move(elems);
  return v;
}

Value Value::makeBuiltin(std::shared_ptr<BuiltinObject> b) {
  Value v;
  v.kind = Kind::Builtin;
  v.builtin = std::move(b);
  return v;
}

Value Value::makeFunction(std::shared_ptr<FunctionObject> f) {
  Value v;
  v.kind = Kind::Function;
  v.fn = std::move(f);
  return v;
}

Value Value::makeClass(std::shared_ptr<ClassObject> c) {
  Value v;
  v.kind = Kind::Class;
  v.klass = std::move(c);
  return v;
}

Value Value::makeInstance(std::shared_ptr<InstanceObject> i) {
  Value v;
  v.kind = Kind::Instance;
  v.instance = std::move(i);
  return v;
}

Value Value::makeBoundMethod(std::shared_ptr<BoundMethodObject> b) {
  Value v;
  v.kind = Kind::BoundMethod;
  v.bound_method = std::move(b);
  return v;
}

Value Value::makeTask(std::shared_ptr<TaskObject> t) {
  Value v;
  v.kind = Kind::Task;
  v.task_handle = std::move(t);
  return v;
}

std::string Value::inspect() const {
  switch (kind) {
    case Kind::Null:
      return "null";
    case Kind::Integer:
      return std::to_string(integer);
    case Kind::Boolean:
      return boolean ? "true" : "false";
    case Kind::String:
      return string_val;
    case Kind::Array: {
      std::ostringstream os;
      os << "[";
      for (size_t i = 0; i < elements->size(); ++i) {
        if (i) os << ", ";
        os << (*elements)[i].inspect();
      }
      os << "]";
      return os.str();
    }
    case Kind::Builtin:
      return "builtin:" + builtin->name;
    case Kind::Function:
      return "fn(" + fn->name + ")";
    case Kind::Class:
      return "class " + klass->name;
    case Kind::Instance:
      return "instance of " + instance->klass->name;
    case Kind::BoundMethod:
      return "bound " + bound_method->method->name;
    case Kind::Task:
      return "task";
  }
  return "?";
}

bool isTruthy(const Value& v) {
  switch (v.kind) {
    case Value::Kind::Null:
      return false;
    case Value::Kind::Boolean:
      return v.boolean;
    case Value::Kind::Integer:
      return v.integer != 0;
    case Value::Kind::String:
      return !v.string_val.empty();
    case Value::Kind::Array:
      return true;
    case Value::Kind::Task:
      return true;
    default:
      return true;
  }
}

bool valueEquals(const Value& a, const Value& b) {
  if (a.kind != b.kind) return false;
  switch (a.kind) {
    case Value::Kind::Null:
      return true;
    case Value::Kind::Integer:
      return a.integer == b.integer;
    case Value::Kind::Boolean:
      return a.boolean == b.boolean;
    case Value::Kind::String:
      return a.string_val == b.string_val;
    case Value::Kind::Array:
      if (a.elements->size() != b.elements->size()) return false;
      for (size_t i = 0; i < a.elements->size(); ++i) {
        if (!valueEquals((*a.elements)[i], (*b.elements)[i])) return false;
      }
      return true;
    case Value::Kind::Task:
      return a.task_handle.get() == b.task_handle.get();
    default:
      return false;
  }
}

std::ostream& operator<<(std::ostream& os, const Value& v) {
  return os << v.inspect();
}
