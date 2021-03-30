class Node(object):
    def TokenLiteral(self):
        pass
    def String(self):
        pass


class Statement(Node):
    def statementNode(self):
        pass


class Expression(Node):
    def expressionNode(self):
        pass


class Program(object):
    statements = []

    #def __init__(self):
    #    self.statements = []

    def TokenLiteral(self):
        if len(self.statements) > 0:
            return self.statements[0].TokenLiteral()
        else:
            return ''

    def String(self):
        for statement in self.statements:
            print statement.String()

    def reset(self):
        self.statements = []


class LetStatement(Statement):
    def __init__(self, token=None):
        self.token = token
        self.name = None
        self.value = None

    def statementNode(self):
        pass

    def TokenLiteral(self):
        return self.token.literal

    def String(self):
        out = ''
        out = out + self.TokenLiteral() + " " + self.name.String() + " := "
        if self.value:
            out = out + self.value.String()
        out = out + ";"
        return out


class ReturnStatement(Statement):
    def __init__(self, token):
        self.token = token
        self.expression = None
        self.returnValue = ''

    def statementNode(self):
        pass

    def TokenLiteral(self):
        return self.token.literal

    def String(self):
        #return 'this is identifier token ' + str(self.token) + '; with expresion ' + str(self.expression)
        out = ''
        out = out + self.TokenLiteral() + ' '
        if self.returnValue:
            out = out + self.returnValue
        out = out + ';'
        return out


class ExpressionStatement(Node):
    def __init__(self, token=None, expression=None):
        self.token = token
        self.expression = expression

    def statementNode(self):
        pass

    def TokenLiteral(self):
        return self.token.literal

    def String(self):
        if self.expression:
            return self.expression.String()
        return ''


class Identifier(object):
    def __init__(self, token=None, value=''):
        self.token = token
        self.value = value

    def expressionNode(self):
        pass

    def TokenLiteral(self):
        return self.token.literal

    def String(self):
        #return 'this is identifier token ' + str(self.token) + '; with value ' + self.value
        return self.value


class IntegerLiteral(object):
    def __init__(self, token=None, value=0):
        self.token = token
        self.value = value

    def expressionNode(self):
        pass

    def TokenLiteral(self):
        return self.token.literal

    def String(self):
        return self.token.literal


class PrefixExpression(object):
    def __init__(self, token=None, operator='', right=None):
        self.token = token
        self.operator = operator
        self.right = right

    def expressionNode(self):
        pass

    def TokenLiteral(self):
        return self.token.literal

    def String(self):
        out = '(' + self.operator + self.right.String() + ')'
        return out


class InflixExpression(object):
    def __init__(self, token=None, left=None, operator=None, right=None):
        self.token = token
        self.left = left
        self.operator = operator if operator else ''
        self.right = right

    def expressionNode(self):
        pass

    def TokenLiteral(self):
        return self.token.literal

    def String(self):
        out = '(' + self.left.String() + self.operator + self.right.String() + ')'
        return out


class Boolean(object):
    def __init__(self, token=None, value=None):
        self.token = token
        self.value = value

    def expressionNode(self):
        pass

    def TokenLiteral(self):
        return self.token.literal

    def String(self):
        out = '[' + self.token.literal + ']'
        return out


class IfExpression(object):
    def __init__(self, token=None, condition=None, consequence=None, alternative=None):
        self.token = token
        self.condition = condition
        self.consequence = consequence
        self.alternative = alternative

    def expressionNode(self):
        pass

    def TokenLiteral(self):
        return self.token.literal

    def String(self):
        out = ''
        out = 'if'
        out = out + self.condition.String()
        out = out + " "
        out = out + self.consequence.String()
        if self.alternative:
            out = out + "else " + self.alternative.String()
        return out


class BlockStatement(object):
    def __init__(self, token, statements):
        self.token = token
        self.statements = statements

    def statementNode(self):
        pass

    def TokenLiteral(self):
        return self.token.literal

    def String(self):
        out = ''
        for statement in self.statements:
            out = out + statement.String()
        return out