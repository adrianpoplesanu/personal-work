class Node(object):
    def __str__(self):
        return 'Node Interface - method not impremented in subclass'

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

    def debug(self):
        for statement in self.statements:
            print statement

class LetStatement(Statement):
    pass

class ReturnStatement(Statement):
    pass

class ExpressionStatement(Statement):
    pass

class IfExpression(Expression):
    pass

class WhileExpression(Expression):
    pass
