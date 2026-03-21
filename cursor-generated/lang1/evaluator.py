from ast_nodes import (
    Program, Identifier, IntegerLiteral, StringLiteral, BooleanLiteral,
    PrefixExpression, InfixExpression, IfExpression, FunctionLiteral,
    CallExpression, ArrayLiteral, IndexExpression,
    LetStatement, ReturnStatement, ExpressionStatement, BlockStatement,
)


class MonkeyObject:
    pass


class IntegerObj(MonkeyObject):
    __slots__ = ("value",)

    def __init__(self, value: int):
        self.value = value

    def __repr__(self):
        return str(self.value)


class StringObj(MonkeyObject):
    __slots__ = ("value",)

    def __init__(self, value: str):
        self.value = value

    def __repr__(self):
        return self.value


class BooleanObj(MonkeyObject):
    __slots__ = ("value",)

    def __init__(self, value: bool):
        self.value = value

    def __repr__(self):
        return "true" if self.value else "false"


TRUE = BooleanObj(True)
FALSE = BooleanObj(False)


class NullObj(MonkeyObject):
    def __repr__(self):
        return "null"


NULL = NullObj()


class ReturnValue(MonkeyObject):
    __slots__ = ("value",)

    def __init__(self, value: MonkeyObject):
        self.value = value


class ErrorObj(MonkeyObject):
    __slots__ = ("message",)

    def __init__(self, message: str):
        self.message = message

    def __repr__(self):
        return f"ERROR: {self.message}"


class FunctionObj(MonkeyObject):
    __slots__ = ("parameters", "body", "env")

    def __init__(self, parameters, body, env):
        self.parameters = parameters
        self.body = body
        self.env = env

    def __repr__(self):
        params = ", ".join(p.value for p in self.parameters)
        return f"fn({params}) {{...}}"


class ArrayObj(MonkeyObject):
    __slots__ = ("elements",)

    def __init__(self, elements: list):
        self.elements = elements

    def __repr__(self):
        return "[" + ", ".join(str(e) for e in self.elements) + "]"


class BuiltinObj(MonkeyObject):
    __slots__ = ("fn",)

    def __init__(self, fn):
        self.fn = fn

    def __repr__(self):
        return "builtin function"


class Environment:
    def __init__(self, outer=None):
        self.store: dict[str, MonkeyObject] = {}
        self.outer = outer

    def get(self, name: str):
        obj = self.store.get(name)
        if obj is None and self.outer is not None:
            return self.outer.get(name)
        return obj

    def set(self, name: str, val: MonkeyObject):
        self.store[name] = val
        return val


def _builtin_len(*args):
    if len(args) != 1:
        return ErrorObj(f"wrong number of arguments. got={len(args)}, want=1")
    arg = args[0]
    if isinstance(arg, StringObj):
        return IntegerObj(len(arg.value))
    if isinstance(arg, ArrayObj):
        return IntegerObj(len(arg.elements))
    return ErrorObj(f"argument to `len` not supported, got {type(arg).__name__}")


def _builtin_puts(*args):
    for arg in args:
        print(arg)
    return NULL


def _builtin_first(*args):
    if len(args) != 1:
        return ErrorObj(f"wrong number of arguments. got={len(args)}, want=1")
    if not isinstance(args[0], ArrayObj):
        return ErrorObj(f"argument to `first` must be ARRAY, got {type(args[0]).__name__}")
    if len(args[0].elements) > 0:
        return args[0].elements[0]
    return NULL


def _builtin_last(*args):
    if len(args) != 1:
        return ErrorObj(f"wrong number of arguments. got={len(args)}, want=1")
    if not isinstance(args[0], ArrayObj):
        return ErrorObj(f"argument to `last` must be ARRAY, got {type(args[0]).__name__}")
    if len(args[0].elements) > 0:
        return args[0].elements[-1]
    return NULL


def _builtin_rest(*args):
    if len(args) != 1:
        return ErrorObj(f"wrong number of arguments. got={len(args)}, want=1")
    if not isinstance(args[0], ArrayObj):
        return ErrorObj(f"argument to `rest` must be ARRAY, got {type(args[0]).__name__}")
    if len(args[0].elements) > 0:
        return ArrayObj(list(args[0].elements[1:]))
    return NULL


def _builtin_push(*args):
    if len(args) != 2:
        return ErrorObj(f"wrong number of arguments. got={len(args)}, want=2")
    if not isinstance(args[0], ArrayObj):
        return ErrorObj(f"argument to `push` must be ARRAY, got {type(args[0]).__name__}")
    return ArrayObj(list(args[0].elements) + [args[1]])


BUILTINS = {
    "len": BuiltinObj(_builtin_len),
    "puts": BuiltinObj(_builtin_puts),
    "first": BuiltinObj(_builtin_first),
    "last": BuiltinObj(_builtin_last),
    "rest": BuiltinObj(_builtin_rest),
    "push": BuiltinObj(_builtin_push),
}


def monkey_eval(node, env: Environment) -> MonkeyObject:
    if isinstance(node, Program):
        return _eval_program(node.statements, env)
    elif isinstance(node, ExpressionStatement):
        return monkey_eval(node.expression, env)
    elif isinstance(node, IntegerLiteral):
        return IntegerObj(node.value)
    elif isinstance(node, StringLiteral):
        return StringObj(node.value)
    elif isinstance(node, BooleanLiteral):
        return TRUE if node.value else FALSE
    elif isinstance(node, PrefixExpression):
        right = monkey_eval(node.right, env)
        if isinstance(right, ErrorObj):
            return right
        return _eval_prefix(node.operator, right)
    elif isinstance(node, InfixExpression):
        left = monkey_eval(node.left, env)
        if isinstance(left, ErrorObj):
            return left
        right = monkey_eval(node.right, env)
        if isinstance(right, ErrorObj):
            return right
        return _eval_infix(node.operator, left, right)
    elif isinstance(node, BlockStatement):
        return _eval_block(node.statements, env)
    elif isinstance(node, IfExpression):
        return _eval_if(node, env)
    elif isinstance(node, LetStatement):
        val = monkey_eval(node.value, env)
        if isinstance(val, ErrorObj):
            return val
        env.set(node.name.value, val)
        return val
    elif isinstance(node, Identifier):
        return _eval_identifier(node, env)
    elif isinstance(node, FunctionLiteral):
        return FunctionObj(node.parameters, node.body, env)
    elif isinstance(node, CallExpression):
        func = monkey_eval(node.function, env)
        if isinstance(func, ErrorObj):
            return func
        args = _eval_expressions(node.arguments, env)
        if len(args) == 1 and isinstance(args[0], ErrorObj):
            return args[0]
        return _apply_function(func, args)
    elif isinstance(node, ReturnStatement):
        val = monkey_eval(node.return_value, env)
        if isinstance(val, ErrorObj):
            return val
        return ReturnValue(val)
    elif isinstance(node, ArrayLiteral):
        elements = _eval_expressions(node.elements, env)
        if len(elements) == 1 and isinstance(elements[0], ErrorObj):
            return elements[0]
        return ArrayObj(elements)
    elif isinstance(node, IndexExpression):
        left = monkey_eval(node.left, env)
        if isinstance(left, ErrorObj):
            return left
        index = monkey_eval(node.index, env)
        if isinstance(index, ErrorObj):
            return index
        return _eval_index(left, index)

    return NULL


def _eval_program(stmts, env):
    result = NULL
    for stmt in stmts:
        result = monkey_eval(stmt, env)
        if isinstance(result, ReturnValue):
            return result.value
        if isinstance(result, ErrorObj):
            return result
    return result


def _eval_block(stmts, env):
    result = NULL
    for stmt in stmts:
        result = monkey_eval(stmt, env)
        if isinstance(result, (ReturnValue, ErrorObj)):
            return result
    return result


def _eval_prefix(operator, right):
    if operator == "!":
        if right is TRUE:
            return FALSE
        if right is FALSE:
            return TRUE
        if right is NULL:
            return TRUE
        if isinstance(right, IntegerObj) and right.value == 0:
            return TRUE
        return FALSE
    elif operator == "-":
        if not isinstance(right, IntegerObj):
            return ErrorObj(f"unknown operator: -{type(right).__name__}")
        return IntegerObj(-right.value)
    return ErrorObj(f"unknown operator: {operator}{type(right).__name__}")


def _eval_infix(operator, left, right):
    if isinstance(left, IntegerObj) and isinstance(right, IntegerObj):
        return _eval_integer_infix(operator, left, right)
    if isinstance(left, StringObj) and isinstance(right, StringObj):
        return _eval_string_infix(operator, left, right)
    if operator == "==":
        return TRUE if left is right else FALSE
    if operator == "!=":
        return TRUE if left is not right else FALSE
    if type(left) != type(right):
        return ErrorObj(f"type mismatch: {type(left).__name__} {operator} {type(right).__name__}")
    return ErrorObj(f"unknown operator: {type(left).__name__} {operator} {type(right).__name__}")


def _eval_integer_infix(operator, left, right):
    lv, rv = left.value, right.value
    if operator == "+":
        return IntegerObj(lv + rv)
    elif operator == "-":
        return IntegerObj(lv - rv)
    elif operator == "*":
        return IntegerObj(lv * rv)
    elif operator == "/":
        if rv == 0:
            return ErrorObj("division by zero")
        return IntegerObj(lv // rv)
    elif operator == "%":
        if rv == 0:
            return ErrorObj("division by zero")
        return IntegerObj(lv % rv)
    elif operator == "<":
        return TRUE if lv < rv else FALSE
    elif operator == ">":
        return TRUE if lv > rv else FALSE
    elif operator == "<=":
        return TRUE if lv <= rv else FALSE
    elif operator == ">=":
        return TRUE if lv >= rv else FALSE
    elif operator == "==":
        return TRUE if lv == rv else FALSE
    elif operator == "!=":
        return TRUE if lv != rv else FALSE
    return ErrorObj(f"unknown operator: IntegerObj {operator} IntegerObj")


def _eval_string_infix(operator, left, right):
    if operator == "+":
        return StringObj(left.value + right.value)
    if operator == "==":
        return TRUE if left.value == right.value else FALSE
    if operator == "!=":
        return TRUE if left.value != right.value else FALSE
    return ErrorObj(f"unknown operator: StringObj {operator} StringObj")


def _eval_if(node, env):
    condition = monkey_eval(node.condition, env)
    if isinstance(condition, ErrorObj):
        return condition
    if _is_truthy(condition):
        return monkey_eval(node.consequence, env)
    elif node.alternative is not None:
        return monkey_eval(node.alternative, env)
    return NULL


def _is_truthy(obj):
    if obj is NULL:
        return False
    if obj is TRUE:
        return True
    if obj is FALSE:
        return False
    return True


def _eval_identifier(node, env):
    val = env.get(node.value)
    if val is not None:
        return val
    builtin = BUILTINS.get(node.value)
    if builtin is not None:
        return builtin
    return ErrorObj(f"identifier not found: {node.value}")


def _eval_expressions(exps, env):
    result = []
    for e in exps:
        evaluated = monkey_eval(e, env)
        if isinstance(evaluated, ErrorObj):
            return [evaluated]
        result.append(evaluated)
    return result


def _apply_function(fn, args):
    if isinstance(fn, FunctionObj):
        if len(args) != len(fn.parameters):
            return ErrorObj(
                f"wrong number of arguments: want={len(fn.parameters)}, got={len(args)}"
            )
        extended_env = Environment(outer=fn.env)
        for param, arg in zip(fn.parameters, args):
            extended_env.set(param.value, arg)
        evaluated = monkey_eval(fn.body, extended_env)
        if isinstance(evaluated, ReturnValue):
            return evaluated.value
        return evaluated
    elif isinstance(fn, BuiltinObj):
        return fn.fn(*args)
    return ErrorObj(f"not a function: {type(fn).__name__}")


def _eval_index(left, index):
    if isinstance(left, ArrayObj) and isinstance(index, IntegerObj):
        idx = index.value
        if idx < 0 or idx >= len(left.elements):
            return NULL
        return left.elements[idx]
    return ErrorObj(f"index operator not supported: {type(left).__name__}")
