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


class Identifier(object):
    def __init__(self, token=None, value=''):
        self.token = token
        self.value = value

    def expressionNode(self):
        pass

    def TokenLiteral(self):
        return self.token.literal

    def String(self):
        return 'this is identifier token ' + str(self.token) + '; with value ' + self.value


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
