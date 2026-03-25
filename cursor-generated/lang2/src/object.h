#pragma once

#include "ast.h"

#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Environment;

struct FunctionObject {
  std::vector<std::string> parameters;
  BlockStatement* body{nullptr};
  std::shared_ptr<Environment> env;
  std::string name;
};

struct BuiltinObject;

struct ClassObject {
  std::string name;
  std::unordered_map<std::string, std::shared_ptr<FunctionObject>> methods;
};

struct InstanceObject;
struct BoundMethodObject;

struct Value {
  enum class Kind {
    Null,
    Integer,
    Boolean,
    String,
    Array,
    Function,
    Builtin,
    Class,
    Instance,
    BoundMethod,
  } kind{Kind::Null};

  int64_t integer{0};
  bool boolean{false};
  std::string string_val;
  std::shared_ptr<std::vector<Value>> elements;
  std::shared_ptr<FunctionObject> fn;
  std::shared_ptr<BuiltinObject> builtin;
  std::shared_ptr<ClassObject> klass;
  std::shared_ptr<InstanceObject> instance;
  std::shared_ptr<BoundMethodObject> bound_method;

  static Value null();
  static Value makeInt(int64_t n);
  static Value makeBool(bool b);
  static Value makeString(std::string s);
  static Value makeArray(std::shared_ptr<std::vector<Value>> elems);
  static Value makeFunction(std::shared_ptr<FunctionObject> f);
  static Value makeBuiltin(std::shared_ptr<BuiltinObject> b);
  static Value makeClass(std::shared_ptr<ClassObject> c);
  static Value makeInstance(std::shared_ptr<InstanceObject> i);
  static Value makeBoundMethod(std::shared_ptr<BoundMethodObject> b);

  std::string inspect() const;
};

struct InstanceObject {
  std::shared_ptr<ClassObject> klass;
  std::unordered_map<std::string, Value> fields;
};

struct BuiltinObject {
  std::string name;
  Value (*fn)(const std::vector<Value>& args);
};

struct BoundMethodObject {
  std::shared_ptr<FunctionObject> method;
  std::shared_ptr<InstanceObject> instance;
};

bool isTruthy(const Value& v);
bool valueEquals(const Value& a, const Value& b);

std::ostream& operator<<(std::ostream& os, const Value& v);
