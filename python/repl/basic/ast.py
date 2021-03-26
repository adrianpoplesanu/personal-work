class Node(object):
    def __str__(self):
        raise Exception("Node Interface - method not implemented in subclass")


class Statement(Node):
    def statement_node(self):
        raise Exception("Statement Interface - method not implemented in subclass")


class Expression(Node):
    def expression_node(self):
        raise Exception("Expression Interface - method not implemented in subclass")


class Program(object):
    def __init__(self, statements=None):
        if statements:
            self.statements = statements
        else:
            self.statements = []

    def debug(self):
        for statement in self.statements:
            print statement

    def reset(self):
        # this won't be needed in the future once the statments are evaluated
        self.statements = []


class LetStatement(Statement):
    pass


class ReturnStatement(Statement):
    pass


class ExpressionStatement(Statement):
    pass


class IfExpression(Expression):
    pass


class Identifier(object):
    pass


class IntegerLiteral(object):
    pass


class PrefixExpression(Expression):
    pass


class InflixExpression(Expression):
    pass


class WhileExpression(Expression):
    pass
