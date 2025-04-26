from typing import List, Dict

from token_ad import Token


class StatementType:
    PROGRAM = 'PROGRAM'
    LET_STATEMENT = 'LET_STATEMENT'
    RETURN_STATEMENT = 'RETURN_STATEMENT'
    EXPRESSION_STATEMENT = 'EXPRESSION_STATEMENT'
    IDENTIFIER = 'IDENTIFIER'
    INTEGER_LITERAL = 'INTEGER_LITERAL'
    FLOAT = 'FLOAT'
    BOOLEAN = 'BOOLEAN'
    INFIX_EXPRESSION = 'INFIX_EXPRESSION'
    PREFIX_EXPRESSION = 'PREFIX_EXPRESSION'
    CALL_EXPRESSION = 'CALL_EXPRESSION'
    IF_EXPRESSION = 'IF_EXPRESSION'
    BLOCK_STATEMENT = 'BLOCK_STATEMENT'
    FUNCTION_LITERAL = 'FUNCTION_LITERAL'
    WHILE_EXPRESSION = 'WHILE_EXPRESSION'
    STRING_LITERAL = 'STRING_LITERAL'
    LIST_LITERAL = 'LIST_LITERAL'
    INDEX_EXPRESSION = 'INDEX_EXPRESSION'
    HASH_LITERAL = 'HASH_LITERAL'
    ASSIGN_STATEMENT = 'ASSIGN_STATEMENT'
    DEF_STATEMENT = 'DEF_STATEMENT'
    CLASS_STATEMENT = 'CLASS_STATEMENT'
    MEMBER_ACCESS = 'MEMBER_ACCESS'
    COMMENT = 'COMMENT'
    PREFIX_INCREMENT = 'PREFIX_INCREMENT'
    POSTFIX_INCREMENT = 'POSTFIX_INCREMENT'
    FOR_EXPRESSION = 'FOR_EXPRESSION'
    NULL_EXPRESSION = 'NULL_EXPRESSION'
    THIS_EXPRESSION = 'THIS_EXPRESSION'
    SUPER_EXPRESSION = 'SUPER_EXPRESSION'
    BREAK_STATEMENT = 'BREAK_STATEMENT'
    CONTINUE_STATEMENT = 'CONTINUE_STATEMENT'
    PLUS_EQUALS_STATEMENT = 'ASSIGN_EQUALS_STATEMENT'


statement_type_map = {
    StatementType.PROGRAM: 'PROGRAM',
    StatementType.EXPRESSION_STATEMENT: 'EXPRESSION_STATEMENT',
    StatementType.INTEGER_LITERAL: 'INTEGER_LITERAL',
    StatementType.INFIX_EXPRESSION: 'INFIX_EXPRESSION',
    StatementType.PREFIX_EXPRESSION: 'PREFIX_EXPRESSION',
    StatementType.BOOLEAN: 'BOOLEAN',
    StatementType.IF_EXPRESSION: 'IF_EXPRESSION',
    StatementType.BLOCK_STATEMENT: 'BLOCK_STATEMENT',
    StatementType.NULL_EXPRESSION: 'NULL_EXPRESSION',
    StatementType.LET_STATEMENT: 'LET_STATEMENT',
    StatementType.IDENTIFIER: 'IDENTIFIER',
    StatementType.STRING_LITERAL: 'STRING_LITERAL',
    StatementType.LIST_LITERAL: 'LIST_LITERAL',
    StatementType.INDEX_EXPRESSION: 'INDEX_EXPRESSION',
    StatementType.HASH_LITERAL: 'HASH_LITERAL',
    StatementType.FUNCTION_LITERAL: 'FUNCTION_LITERAL',
    StatementType.CALL_EXPRESSION: 'CALL_EXPRESSION',
    StatementType.ASSIGN_STATEMENT: 'ASSIGN_STATEMENT',
    StatementType.RETURN_STATEMENT: 'RETURN_STATEMENT',
    StatementType.WHILE_EXPRESSION: 'WHILE_EXPRESSION'
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


class ASTString(ASTNode):
    statement_type = StatementType.STRING_LITERAL

    def __init__(self, token: Token, value: str = None):
        self.token = token
        self.value = value

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return 'ASTString[' + self.value + ']'


class ASTList(ASTNode):
    statement_type = StatementType.LIST_LITERAL

    def __init__(self, token: Token = None, elements: List = None):
        super().__init__()
        self.token = token
        self.elements = elements

    def token_literal(self) -> str:
        return self.token.literal

    def __str__(self) -> str:
        return '[' + ','.join([str(element) for element in self.elements]) + ']'


class ASTIndexExpression(ASTNode):
    statement_type = StatementType.INDEX_EXPRESSION

    def __init__(self, token: Token = None, left: ASTNode = None, index: ASTNode = None):
        super().__init__()
        self.token = token
        self.left = left
        self.index = index

    def token_literal(self) -> str:
        return self.token.literal

    def __str__(self) -> str:
        return 'ASTIndexExpression<' + str(self.left) + '>[' + str(self.index) + ']'


class ASTHash(ASTNode):
    statement_type = StatementType.HASH_LITERAL

    def __init__(self, token: Token = None, pairs: Dict[ASTNode, ASTNode] = None):
        """
        @param token: the node's token
        @param pairs: map [Expression] => Expression
        """
        super().__init__()
        self.token = token
        self.pairs = pairs

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        out = 'ASTHashLiteral['
        for key, value in self.pairs.items():
            out += "<" + str(key) + ": " + str(value) + ">"
        out += "]"
        return out


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


class ASTIfExpression(ASTNode):
    statement_type = StatementType.IF_EXPRESSION

    def __init__(self, token=None, condition=None, consequence=None, alternative=None):
        """
        @param token: the node's token
        @param condition: expression???
        @param consequence: ASTBlockStatement
        @param alternative: ASTBlockStatement
        """
        self.token = token
        self.condition = condition
        self.consequence = consequence
        self.alternative = alternative

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return 'ASTIfExpression'


class ASTBlockStatement(ASTNode):
    statement_type = StatementType.BLOCK_STATEMENT

    def __init__(self, token=None, statements=None):
        """
        @param token: the node's token
        @param statements: list
        """
        self.token = token
        if statements:
            self.statements = statements
        else:
            self.statements = []

    def __str__(self):
        out = ""
        for statement in self.statements:
            out += str(statement)
        return out


class ASTLetStatement(ASTNode):
    statement_type = StatementType.LET_STATEMENT

    def __init__(self, token=None, name=None, value=None):
        self.token = token
        self.name = name
        self.value = value

    def __str__(self):
        return 'ASTLetStatement<' + str(self.name) + '> [' + str(self.value) + ']'


class ASTFunctionLiteral(ASTNode):
    statement_type = StatementType.FUNCTION_LITERAL

    def __init__(self, token=None, parameters=None, default_params=None, body=None, name: str = None):
        super().__init__()
        self.token = token
        self.parameters = parameters
        self.default_params = default_params
        self.body = body
        self.name = name

    def __str__(self):
        return 'ASTFunctionLiteral'


class ASTCallExpression(ASTNode):
    statement_type = StatementType.CALL_EXPRESSION

    def __init__(self, token=None, func=None):
        super().__init__()
        self.token = token
        self.func = func
        self.arguments = None
        self.kw_args = None

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return 'ASTCallExpression[some arguments here]'


class ASTReturnStatement(ASTNode):
    statement_type = StatementType.RETURN_STATEMENT

    def __init__(self, token: Token = None, value: ASTNode = None):
        super().__init__()
        self.token = token
        self.value = value

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return 'ASTReturnStatement[some arguments here]'


class ASTIdentifier(ASTNode):
    statement_type = StatementType.IDENTIFIER

    def __init__(self, token: Token = None, value: str = None):
        super().__init__()
        self.token = token
        self.value = value

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return 'ASTIdentifier[' + self.value + ']'


class ASTNullExpression(ASTNode):
    statement_type = StatementType.NULL_EXPRESSION

    def __init__(self, token=None):
        self.token = token

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return "ASTNullExpression"


class ASTThisExpression(ASTNode):
    statement_type = StatementType.THIS_EXPRESSION

    def __init__(self, token=None):
        """
        @param token: the node's token
        """
        super().__init__()
        self.token = token

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return 'Token: ' + str(self.token)


class ASTMemberAccess(ASTNode):
    statement_type = StatementType.MEMBER_ACCESS

    def __init__(self, token=None, arguments=None, kw_args=None, owner=None, member=None, is_method=False):
        """
        @param token: the node's token
        @param arguments:
        @param owner:
        @param member:
        @param is_method: boolean, indicates is this member access is a method call or an attribute access
        """
        super().__init__()
        self.token = token
        self.arguments = arguments
        self.kw_args = kw_args
        self.owner = owner
        self.member = member
        self.is_method = is_method

    def __str__(self):
        return "ASTMemberAccess{owner: " + str(self.owner) + ", member: " + str(self.member) + "}"


class ASTDefStatement(ASTNode):
    statement_type = StatementType.DEF_STATEMENT

    def __init__(self, token: Token = None, name=None, parameters=None, default_params=None, body=None):
        """
        @param name: AstNode - identifier that will store the function, it needs to be like a let statement in the eval
        @param parameters: AstNode[] list of funtion argumentss
        @:param default_params: default params when missing argument
        @param body: AstNode block statement that is the body of the function
        """
        super().__init__()
        self.name = name
        self.token = token
        self.parameters = parameters
        self.default_params = default_params
        self.body = body

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return 'Token: ' + str(self.token) + '<name: ' + str(self.name) + ', params:' + str(
            self.parameters) + ', body: ' + str(self.body) + '>'


class ASTAssignStatement(ASTNode):
    statement_type = StatementType.ASSIGN_STATEMENT

    def __init__(self, token: Token = None, name: ASTNode = None, value: ASTNode = None):
        super().__init__()
        self.token = token
        self.name = name
        self.value = value

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        if self.name.statement_type == StatementType.MEMBER_ACCESS:
            return 'AssignStatement [' + str(self.token.literal) + '] <' + str(self.name) + '>: ' + (
                str(self.value) if self.value else '')
        return 'AssignStatement [' + str(self.token.literal) + '] <' + str(self.name.value) +'>: ' + (str(self.value) if self.value else '')


class ASTClassStatement(ASTNode):
    statement_type = StatementType.CLASS_STATEMENT

    def __init__(self, token: Token = None, name: ASTNode = None, methods: List[ASTDefStatement] = None,
                 attributes: List[ASTAssignStatement] = None, inherit_from: List[ASTNode] = None):
        """
        @param token: the node's token
        @param name: ASTIdentifier, name of the class
        @param methods: list of ASTDefStatement
        @param attributes: list of ASTAssignStatement
        @param inherit_from: list of parents the class inherits from, should this be a list of ASTNode(s)?
        """
        super().__init__()
        self.token = token
        self.name = name
        self.methods = methods
        self.attributes = attributes
        self.inherit_from = inherit_from

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return 'Token: ' + str(self.token)


class ASTWhileExpression(ASTNode):
    statement_type = StatementType.WHILE_EXPRESSION

    def __init__(self, token: Token = None, condition: ASTNode = None, block: ASTNode = None):
        """
        @param token: the node's token
        @param condition: expression???
        @param block: ASTBlockStatement
        """
        super().__init__()
        self.token = token
        self.condition = condition
        self.block = block

    def token_literal(self):
        return self.token.literal

    def __str__(self):
        return 'TODO: implement __str__ in ASTWhileExpression'
