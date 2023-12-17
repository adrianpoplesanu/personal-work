from token import Token


class StatementType:
    PROGRAM = 'PROGRAM'
    EXPRESSION_STATEMENT = 'EXPRESSION_STATEMENT'


statement_type_map = {
    StatementType.PROGRAM: 'PROGRAM',
    StatementType.EXPRESSION_STATEMENT: 'EXPRESSION_STATEMENT'
}


class ASTNode:
    def token_literal(self):
        print ('token_literal unimplemented in subclass')

    def __str__(self):
        print ('__str__ not implmented in subclass')


class ASTProgram(ASTNode):
    type = StatementType.PROGRAM

    def __init__(self):
        self.statements = []

    def reset(self):
        self.statements = []


class ASTExpressionStatement(ASTNode):
    def __init__(self, token: Token, expression: ASTNode = None):
        self.token = token
        self.expression = expression


class ASTInteger(ASTNode):
    def __init__(self, token: Token, value: int = None):
        self.token = token
        self.value = value


class ASTInfixExpression(ASTNode):
    def __init__(self, token=None, operator=None, left=None, right=None):
        self.token = token
        self.operator = operator
        self.left = left
        self.right = right
