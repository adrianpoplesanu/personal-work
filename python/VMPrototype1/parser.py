from typing import Optional

from ast import ASTProgram, ASTNode, ASTExpressionStatement, ASTInteger, ASTInfixExpression, ASTPrefixExpression, \
    ASTBoolean, ASTIfExpression, ASTBlockStatement, ASTNullExpression, ASTLetStatement, ASTIdentifier, ASTString, \
    ASTList, ASTIndexExpression, ASTHash
from lexer import Lexer
from precedence_type import PrecedenceType, precedences
from token_type import TokenType


class Parser:
    def __init__(self):
        self.source = None
        self.lexer = Lexer()
        self.current_token = None
        self.peek_token = None
        self.statement_parse_fns = {
            TokenType.IF: self.parse_if_statement
        }

        self.prefix_parse_fns = {
            TokenType.IDENT: self.parse_identifier,
            TokenType.INT: self.parse_integer_literal,
            TokenType.TRUE: self.parse_boolean,
            TokenType.FALSE: self.parse_boolean,
            TokenType.BANG: self.parse_prefix_expression,
            TokenType.MINUS: self.parse_prefix_expression,
            TokenType.LPAREN: self.parse_grouped_expression,
            TokenType.IF: self.parse_if_statement,
            TokenType.NULL: self.parse_null_expression,
            TokenType.STRING: self.parse_string_literal,
            TokenType.LBRACKET: self.parse_list_literal,
            TokenType.LBRACE: self.parse_hash_literal
        }

        self.infix_parse_fns = {
            TokenType.PLUS: self.parse_infix_expression,
            TokenType.MINUS: self.parse_infix_expression,
            TokenType.ASTERISK: self.parse_infix_expression,
            TokenType.SLASH: self.parse_infix_expression,
            TokenType.EQ: self.parse_infix_expression,
            TokenType.NOT_EQ: self.parse_infix_expression,
            TokenType.GT: self.parse_infix_expression,
            TokenType.LT: self.parse_infix_expression,
            TokenType.GTE: self.parse_infix_expression,
            TokenType.LTE: self.parse_infix_expression,
            TokenType.LBRACKET: self.parse_index_expression
        }

    def load(self, source):
        self.source = source
        self.lexer.load(source)
        self.next_token()
        self.next_token()

    def build_program_statements(self, program: ASTProgram):
        while self.current_token.token_type != TokenType.EOF:
            # print(self.current_token)
            stmt = self.parse_statement()
            if stmt:
                program.statements.append(stmt)
            self.next_token()

    def next_token(self):
        self.current_token = self.peek_token
        self.peek_token = self.lexer.next_token()

    def current_token_is(self, token_type : TokenType):
        return self.current_token.token_type == token_type

    def peek_token_is(self, token_type: TokenType):
        return self.peek_token.token_type == token_type

    def expect_peek(self, token_type: TokenType) -> bool:
        if self.peek_token_is(token_type):
            self.next_token()
            return True
        else:
            #self.errors.append('ERROR: i was expecting a different token here: ' + token_type)
            print('ERROR: i was expecting a different token here: ' + str(token_type))
            return False

    def peek_precedence(self):
        if self.peek_token.token_type in precedences:
            return precedences[self.peek_token.token_type]
        return PrecedenceType.LOWEST

    def current_precedence(self):
        if self.current_token.token_type in precedences:
            return precedences[self.current_token.token_type]
        return PrecedenceType.LOWEST

    def parse_statement(self) -> Optional[ASTNode]:
        #if self.current_token.token_type in self.statement_parse_fns:
        #    return self.statement_parse_fns[self.current_token.token_type]()
        if self.current_token.token_type == TokenType.LET:
            return self.parse_let_expression()
        return self.parse_expression_statement()

    def parse_identifier(self) -> ASTNode:
        stmt = ASTIdentifier(token=self.current_token, value=self.current_token.literal)
        return stmt

    def parse_integer_literal(self) -> ASTNode:
        stmt = ASTInteger(token=self.current_token, value=int(self.current_token.literal))
        return stmt

    def parse_boolean(self) -> ASTNode:
        stmt = ASTBoolean(token=self.current_token, value=bool(self.current_token.token_type == TokenType.TRUE))
        return stmt

    def parse_expression_statement(self) -> Optional[ASTNode]:
        stmt = ASTExpressionStatement(token=self.current_token)
        stmt.expression = self.parse_expression(PrecedenceType.LOWEST)
        if self.peek_token_is(TokenType.SEMICOLON):
            self.next_token()
        return stmt

    def parse_prefix_expression(self) -> ASTNode:
        expr = ASTPrefixExpression(token=self.current_token, operator=self.current_token.literal)
        self.next_token()
        expr.right = self.parse_expression(PrecedenceType.PREFIX)
        return expr

    def parse_grouped_expression(self) -> Optional[ASTNode]:
        self.next_token()
        expr = self.parse_expression(PrecedenceType.LOWEST)
        if not self.expect_peek(TokenType.RPAREN):
            return None
        return expr

    def parse_if_statement(self) -> Optional[ASTNode]:
        expr = ASTIfExpression(token=self.current_token)
        if not self.expect_peek(TokenType.LPAREN):
            return None
        self.next_token()
        expr.condition = self.parse_expression(PrecedenceType.LOWEST)
        if not self.expect_peek(TokenType.RPAREN):
            return None
        if not self.expect_peek(TokenType.LBRACE):
            expr.consequence = self.parse_single_block_statement()
        else:
            expr.consequence = self.parse_block_statement()
        if self.peek_token_is(TokenType.ELSE):
            self.next_token()
            if not self.expect_peek(TokenType.LBRACE):
                expr.alternative = self.parse_single_block_statement()
            else:
                expr.alternative = self.parse_block_statement()
        return expr

    def parse_block_statement(self):
        block = ASTBlockStatement(token=self.current_token)
        self.next_token()
        while (not self.current_token_is(TokenType.RBRACE)) and (not self.current_token_is(TokenType.EOF)):
            stmt = self.parse_statement()
            if stmt:
                block.statements.append(stmt)
            self.next_token()
        return block

    def parse_single_block_statement(self):
        block = ASTBlockStatement(token=self.current_token)
        self.next_token()
        stmt = self.parse_statement()
        block.statements.append(stmt)
        return block

    def parse_null_expression(self) -> ASTNode:
        expr = ASTNullExpression(token=self.current_token)
        self.next_token()
        return expr

    def parse_string_literal(self) -> ASTNode:
        return ASTString(token=self.current_token, value=str(self.current_token.literal))

    def parse_list_literal(self) -> ASTNode:
        expr = ASTList(self.current_token)
        expr.elements = self.parse_expression_list()
        return expr

    def parse_hash_literal(self) -> Optional[ASTNode]:
        node = ASTHash(token=self.current_token)
        node.pairs = {}
        while not self.peek_token_is(TokenType.RBRACE):
            self.next_token()
            key = self.parse_expression(PrecedenceType.LOWEST)
            if not self.expect_peek(TokenType.COLON):
                return None
            self.next_token()
            value = self.parse_expression(PrecedenceType.LOWEST)
            node.pairs[key] = value
            if not self.peek_token_is(TokenType.RBRACE) and not self.expect_peek(TokenType.COMMA):
                return None
        if not self.expect_peek(TokenType.RBRACE):
            return None
        return node

    def parse_expression_list(self):
        elements = []
        if self.peek_token_is(TokenType.RBRACKET):
            self.next_token()
            return elements
        self.next_token()
        elements.append(self.parse_expression(PrecedenceType.LOWEST))
        while self.peek_token_is(TokenType.COMMA):
            self.next_token()
            self.next_token()
            elements.append(self.parse_expression(PrecedenceType.LOWEST))
        if not self.expect_peek(TokenType.RBRACKET):
            return None
        return elements

    def parse_index_expression(self, left: ASTNode) -> Optional[ASTNode]:
        expr = ASTIndexExpression(token=self.current_token, left=left)
        self.next_token()
        expr.index = self.parse_expression(PrecedenceType.LOWEST)
        if not self.expect_peek(TokenType.RBRACKET):
            return None
        return expr

    def parse_let_expression(self):
        stmt = ASTLetStatement(token=self.current_token)
        if not self.expect_peek(TokenType.IDENT):
            return None
        stmt.name = ASTIdentifier(token=self.current_token, value=self.current_token.literal)
        if not self.expect_peek(TokenType.ASSIGN):
            return None
        self.next_token()
        stmt.value = self.parse_expression(PrecedenceType.LOWEST)
        if self.current_token_is(TokenType.SEMICOLON):
            self.next_token()
        return stmt

    def parse_infix_expression(self, left: ASTNode) -> ASTNode:
        expr = ASTInfixExpression(token=self.current_token, operator=self.current_token.literal, left=left)
        precedence = self.current_precedence()
        self.next_token()
        expr.right = self.parse_expression(precedence)
        return expr

    def parse_expression(self, precedence) -> Optional[ASTNode]:
        if self.current_token.token_type not in self.prefix_parse_fns:
            return None
        prefix = self.prefix_parse_fns[self.current_token.token_type]
        left_exp: Optional[ASTNode] = prefix()
        while (not self.peek_token_is(TokenType.SEMICOLON)) and precedence < self.peek_precedence():
            if self.peek_token.token_type not in self.infix_parse_fns:
                return left_exp
            infix = self.infix_parse_fns[self.peek_token.token_type]
            self.next_token()
            left_exp = infix(left_exp)
        return left_exp
