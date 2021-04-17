from ast import IntegerLiteral
from object import ObjectType
from object import Integer
from object import Boollean
from ast import Program, IntegerLiteral, ExpressionStatement, Boolean


def Eval(node):
    #print node
    #print type(node)
    #print type(Program)
    #print type(node) == Program
    if type(node) == Program:
        return evalStatements(node.statements)
    elif type(node) == IntegerLiteral:
        return Integer(Value=node.value)
    elif type(node) == Boolean:
        #print '###' + str(node.value) + '###'
        return Boollean(Value=node.value)
    elif type(node) == ExpressionStatement:
        return Eval(node.expression)
    else:
        print 'evaluatorul nu stie ce sa faca cu nodul asta'
        #raise Exception("Evaluatorul nu stie ce sa faca cu nodul asta")
    return None

def evalStatements(statements):
    result = None
    for statement in statements:
        result = Eval(statement)
    return result