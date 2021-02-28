class Node(object):
    pass

class Statement(Node):
    pass

class Expression(Node):
    pass

class Program(object):
    def __init__(self, statements=None):
        if statements:
            self.statements = statements
        else:
            self.statements = []

class LetStatement(Statement):
    pass

class ReturnStatement(Statement):
    pass

class ExpressionStatement(Statement):
    pass

class IfExpression(Expression):
    pass

class ForExpression(Expression):
    pass
