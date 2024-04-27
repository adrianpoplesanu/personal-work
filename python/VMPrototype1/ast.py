from token_ad import Token


class StatementType:
    PROGRAM = 'PROGRAM'
    EXPRESSION_STATEMENT = 'EXPRESSION_STATEMENT'
    INTEGER_LITERAL = 'INTEGER_LITERAL'
    INFIX_EXPRESSION = 'INFIX_EXPRESSION'
    PREFIX_EXPRESSION = 'PREFIX_EXPRESSION'
    BOOLEAN = 'BOOLEAN'


statement_type_map = {
    StatementType.PROGRAM: 'PROGRAM',
    StatementType.EXPRESSION_STATEMENT: 'EXPRESSION_STATEMENT',
    StatementType.INTEGER_LITERAL: 'INTEGER_LITERAL',
    StatementType.INFIX_EXPRESSION: 'INFIX_EXPRESSION',
    StatementType.PREFIX_EXPRESSION: 'PREFIX_EXPRESSION',
    StatementType.BOOLEAN: 'BOOLEAN'
}


class ASTNode:
    statement_type = None

    def __init__(self):
        pass

    def token_literal(self):
        print('token_literal unimplemented in subclass')

    def __str__(self):
        print('__str__ unimplemented in subclass')


class ASTProgram(ASTNode):
    statement_type = StatementType.PROGRAM

    def __init__(self):
        self.statements = []

    def reset(self):
        self.statements = []

    def token_literal(self):
        return "PROGRAM"

    def __str__(self):
        return 'ASTProgram\n' + '\n'.join([str(stmt) for stmt in self.statements])


class ASTExpressionStatement(ASTNode):
    statement_type = StatementType.EXPRESSION_STATEMENT

    def __init__(self, token: Token, expression: ASTNode = None):
        self.token = token
        self.expression = expression

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return 'ASTExpressionStatement[' + str(self.expression) + ']'


class ASTInteger(ASTNode):
    statement_type = StatementType.INTEGER_LITERAL

    def __init__(self, token: Token, value: int = None):
        self.token = token
        self.value = value

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return 'ASTInteger[' + str(self.value) + ']'


class ASTInfixExpression(ASTNode):
    statement_type = StatementType.INFIX_EXPRESSION

    def __init__(self, token=None, operator=None, left=None, right=None):
        self.token = token
        self.operator = operator
        self.left = left
        self.right = right

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return "ASTInfixExpression [{0} <{1}> {2}]".format(str(self.left), str(self.operator), str(self.right))


class ASTPrefixExpression(ASTNode):
    statement_type = StatementType.PREFIX_EXPRESSION

    def __init__(self, token=None, operator=None, right=None):
        self.token = token
        self.operator = operator
        self.right = right

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return "ASTPrefixExpression <{0}> [{1}]".format(self.operator, self.right)


class ASTBoolean(ASTNode):
    statement_type = StatementType.BOOLEAN

    def __init__(self, token: Token, value: bool = None):
        self.token = token
        self.value = value

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return 'ASTBoolean[' + str(self.value) + ']'
