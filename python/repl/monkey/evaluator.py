from ast import IntegerLiteral
from object import ObjectType
from object import Integer as IntegerObject
from object import Boolean as BooleanObject
from object import Null as NullObject
from object import ReturnValue as ReturnValue
from object import Function as FunctionObject
from object import String as StringObject
from object import Error as Error
from object import Builtin as BuiltinObject
from object import ArrayObject as ArrayObject
from ast import Program, IntegerLiteral, ExpressionStatement, \
                Boolean, PrefixExpression, InfixExpression, BlockStatement, \
                IfExpression, ReturnStatement, LetStatement, Identifier, \
                CallExpression, FunctionLiteral, StringLiteral, ArrayLiteral, \
                IndexExpression
from builtins import builtins_map
from environment import NewEnclosedEnvironment
from utils import print_ast_node

NULL = NullObject()
TRUE = BooleanObject(Value=True)
FALSE = BooleanObject(Value=False)
ERROR_OBJ = Error(message="nu stiu ce e cu eroare asta")

def Eval(node, env):
    if type(node) == Program:
        return evalProgram(node, env)
    elif type(node) == IntegerLiteral:
        return IntegerObject(Value=node.value) # in python there is a list of small ints and a small int value is returned from that list
    elif type(node) == Boolean:
        return nativeBoolToBooleanObject(node.value)
    elif type(node) == ExpressionStatement:
        return Eval(node.expression, env)
    elif type(node) == PrefixExpression:
        right = Eval(node.right, env)
        if isError(right):
            return right
        return evalPrefixExpression(node.operator, right)
    elif type(node) == InfixExpression:
        left = Eval(node.left, env)
        if isError(left):
            return left
        right = Eval(node.right, env)
        if isError(right):
            return right
        return evalInfixExpression(node.operator, left, right)
    elif type(node) == BlockStatement:
        return evalBlockStatement(node, env)
    elif type(node) == IfExpression:
        return evalIfExpression(node, env)
    elif type(node) == ReturnStatement:
        val = Eval(node.returnValue, env)
        if isError(val):
            return val
        return ReturnValue(Value=val)
    elif type(node) == LetStatement:
        val = Eval(node.value, env)
        if isError(val):
            return val
        env.Set(node.name.String(), val) # aici poate e doar node.name, sau node.value
    elif type(node) == Identifier:
        return evalIdentifier(node, env)
    elif type(node) == CallExpression:
        function = Eval(node.function, env)
        if isError(function):
            return function
        args = evalExpressions(node.arguments, env)
        if len(args) == 1 and isError(args[0]):
            return args[0]
        return applyFunction(function, args)
    elif type(node) == FunctionLiteral:
        params = node.parameters
        body = node.body
        return FunctionObject(parameters=params, body=body, env=env)
    elif type(node) == StringLiteral:
        return StringObject(value=node.value)
    elif type(node) == ArrayLiteral:
        elements = evalExpressions(node.elements, env)
        if len(elements) == 1 and isError(element[0]):
            return elements[0]
        return ArrayObject(elements=elements)
    elif type(node) == IndexExpression:
        left = Eval(node.left, env)
        if isError(left):
            return left
        index = Eval(node.index, env)
        if isError(index):
            return index
        return evalIndexExpression(left, index)
    else:
        # daca node e None, probabil nodul e ;
        # TODO: if a new ast node EmptyInstruction is implemented, i could check for that
        if not node:
            return None
        print 'evaluatorul nu stie ce sa faca cu nodul asta: ' + str(node)
        #raise Exception("Evaluatorul nu stie ce sa faca cu nodul asta")
    return None

def evalProgram(node, env):
    result = None
    for statement in node.statements:
        #print_ast_node(statement, 0)
        result = Eval(statement, env)
        # i don't understand the Go code here in order to translate it
        try:
            #returnValue, ok = result.returnValue
            if result and type(result) == ReturnValue:
                #return result.Value.Value # this might need to be uncommented in the future
                return result.Value
            elif result and type(result) == Error:
                return result
        except:
            pass
    return result

def evalBlockStatement(node, env):
    result = None
    for statement in node.statements:
        result = Eval(statement, env)
        if result:
            rt = result.Type()
            if rt == ObjectType.RETURN_VALUE_OBJ or rt == ObjectType.ERROR_OBJ:
                return result
    return result

def nativeBoolToBooleanObject(value):
    if value:
        return TRUE
    return FALSE

def evalPrefixExpression(operator, right):
    if operator == '!':
        return evalBangOperatorExpression(right)
    if operator == '-':
        return evalMinusPrefixOperatorExpression(right)
    #return NULL
    return newError("unknown operator: {0}{0}".format(operator, right.Type()))

def evalBangOperatorExpression(right):
    if right == TRUE:
        return FALSE
    elif right == FALSE:
        return TRUE
    elif right == NULL:
        return TRUE
    else:
        return FALSE

def evalMinusPrefixOperatorExpression(right):
    #if right.Type() != object.INTEGER_OBJ:
    #    return newError("unknown operator: -{0}".format(right.Type()))
    if right.Type() != ObjectType.INTEGER_OBJ:
        return None
    value = right.Value;
    return IntegerObject(Value=-value)

def evalInfixExpression(operator, left, right):
    if left.Type() == ObjectType.INTEGER_OBJ and right.Type() == ObjectType.INTEGER_OBJ:
        return evalIntegerInfixExpression(operator, left, right)
    elif left.Type() == ObjectType.STRING_OBJ and right.Type() == ObjectType.STRING_OBJ:
        return evalStringInfixExpression(operator, left, right)
    elif operator == '==':
        return nativeBoolToBooleanObject(left == right)
    elif operator == '!=':
        return nativeBoolToBooleanObject(left != right)
    elif left.Type() != right.Type():
        return newError("type mismatch: {0} {1} {2}".format(left.Type(), operator, right.Type()))
    else:
        return newError("unknown operator: {0} {1} {2}".format(left.Type(), operator, right.Type()))

def evalIntegerInfixExpression(operator, left, right):
    leftVal = left.Value
    rightVal = right.Value
    if operator == '+':
        return IntegerObject(Value=leftVal+rightVal)
    elif operator == '-':
        return IntegerObject(Value=leftVal-rightVal)
    elif operator == '/':
        return IntegerObject(Value=leftVal/rightVal)
    elif operator == '*':
        return IntegerObject(Value=leftVal*rightVal)
    elif operator == '<':
        # print type(leftVal) # asta returneaza tipul nativ din python
        return nativeBoolToBooleanObject(leftVal < rightVal)
    elif operator == '>':
        return nativeBoolToBooleanObject(leftVal > rightVal)
    elif operator == '==':
        return nativeBoolToBooleanObject(leftVal == rightVal)
    elif operator == '!=':
        return nativeBoolToBooleanObject(leftVal != rightVal)
    else:
        #return NULL
        return newError("unknown operator: %s %s %s".format(left.Type(), operator, right.Type()))

def evalStringInfixExpression(operator, left, right):
    if operator != '+':
        return newError("unknown operator: %s %s %s".format(left.Type(), operator, right.Type()))
    left_val = left.value
    right_val = right.value
    return StringObject(value=left_val+right_val)

def evalIfExpression(node, env):
    condition = Eval(node.condition, env)
    if isError(condition):
        return condition
    if isTruthy(condition):
        return Eval(node.consequence, env)
    elif node.alternative:
        return Eval(node.alternative, env)
    else:
        return NULL

def evalIdentifier(node, env):
    val, check = env.Get(node.value)
    if check:
        return val
    if node.value in builtins_map:
        return builtins_map[node.value]
    return newError("identifier referenced before assign")

def evalExpressions(exps, env):
    result = []
    for exp in exps:
        evaluated = Eval(exp, env)
        if isError(evaluated):
            return evaluated
        result.append(evaluated)
    return result

def applyFunction(fn, args):
    if type(fn) == FunctionObject:
        extendedEnv = extendFunctionEnv(fn, args)
        evaluated = Eval(fn.body, extendedEnv)
        return unwrapReturnValue(evaluated)
    elif type(fn) == BuiltinObject:
        return fn.builtin_function(*args)
    return newError("not a function {0}".format(fn.Type()))

def extendFunctionEnv(fn, args):
    env = NewEnclosedEnvironment(fn.env)

    for i, param in enumerate(fn.parameters):
        env.Set(param.value, args[i])
    return env

def unwrapReturnValue(obj):
    if type(obj) == ReturnValue:
        return obj.Value
    return obj

def evalIndexExpression(left, index):
    if left.Type() == ObjectType.ARRAY_OBJ and index.Type() == ObjectType.INTEGER_OBJ:
        return evalArrayIndexExpression(left, index)
    else:
        return newError("error evaluating index expression")

def evalArrayIndexExpression(left, index):
    array_object = left
    idx = index.Value
    max = len(array_object.elements) - 1
    if idx < 0 or idx > max:
        return None
    return array_object.elements[idx]

def isTruthy(obj):
    if obj == NULL:
        return False
    elif obj == TRUE:
        return True
    elif obj == FALSE:
        return False
    else:
        return True

def newError(text):
    return Error(message=text)

def isError(obj):
    return obj.Type() == ERROR_OBJ