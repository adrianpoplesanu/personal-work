from ast import IntegerLiteral
from object import ObjectType
from object import Integer as IntegerObject
from object import Boolean as BooleanObject
from object import Null as NullObject
from ast import Program, IntegerLiteral, ExpressionStatement, Boolean, PrefixExpression, InfixExpression

NULL = NullObject()
TRUE = BooleanObject(Value=True)
FALSE = BooleanObject(Value=False)

def Eval(node):
    #print node
    #print type(node)
    #print type(Program)
    #print type(node) == Program
    if type(node) == Program:
        return evalStatements(node.statements)
    elif type(node) == IntegerLiteral:
        return IntegerObject(Value=node.value) # in python there is a list of small ints and a small int value is returned from that list
    elif type(node) == Boolean:
        #print '###' + str(node.value) + '###'
        #return BooleanObject(Value=node.value)
        return nativeBoolToBooleanObject(node.value)
    elif type(node) == ExpressionStatement:
        return Eval(node.expression)
    elif type(node) == PrefixExpression:
        right = Eval(node.right)
        return evalPrefixExpression(node.operator, right)
    elif type(node) == InfixExpression:
        left = Eval(node.left)
        right = Eval(node.right)
        return evalInfixExpression(node.operator, left, right)
    else:
        print 'evaluatorul nu stie ce sa faca cu nodul asta'
        #raise Exception("Evaluatorul nu stie ce sa faca cu nodul asta")
    return None

def evalStatements(statements):
    result = None
    for statement in statements:
        result = Eval(statement)
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
    return NULL

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
    if right.Type() != ObjectType.INTEGER_OBJ:
        return None
    value = right.Value;
    return IntegerObject(Value=-value)

def evalInfixExpression(operator, left, right):
    if left.Type() == ObjectType.INTEGER_OBJ and right.Type() == ObjectType.INTEGER_OBJ:
        return evalIntegerInfixExpression(operator, left, right)
    else:
        return None

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
    else:
        return NULL