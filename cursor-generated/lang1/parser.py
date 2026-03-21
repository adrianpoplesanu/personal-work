from tokens import Token, TokenType
from lexer import Lexer
from ast_nodes import (
    Program, Identifier, IntegerLiteral, StringLiteral, BooleanLiteral,
    PrefixExpression, InfixExpression, IfExpression, FunctionLiteral,
    CallExpression, ArrayLiteral, IndexExpression,
    LetStatement, ReturnStatement, ExpressionStatement, BlockStatement,
)

LOWEST = 1
EQUALS = 2
LESSGREATER = 3
SUM = 4
PRODUCT = 5
PREFIX = 6
CALL = 7
INDEX = 8

PRECEDENCES = {
    TokenType.EQ: EQUALS,
    TokenType.NOT_EQ: EQUALS,
    TokenType.LT: LESSGREATER,
    TokenType.GT: LESSGREATER,
    TokenType.LT_EQ: LESSGREATER,
    TokenType.GT_EQ: LESSGREATER,
    TokenType.PLUS: SUM,
    TokenType.MINUS: SUM,
    TokenType.SLASH: PRODUCT,
    TokenType.ASTERISK: PRODUCT,
    TokenType.PERCENT: PRODUCT,
    TokenType.LPAREN: CALL,
    TokenType.LBRACKET: INDEX,
}


class Parser:
    def __init__(self, lexer: Lexer):
        self.lexer = lexer
        self.errors: list[str] = []
        self.cur_token = Token(TokenType.EOF, "")
        self.peek_token = Token(TokenType.EOF, "")
        self._next_token()
        self._next_token()

    def _next_token(self):
        self.cur_token = self.peek_token
        self.peek_token = self.lexer.next_token()

    def _cur_precedence(self) -> int:
        return PRECEDENCES.get(self.cur_token.type, LOWEST)

    def _peek_precedence(self) -> int:
        return PRECEDENCES.get(self.peek_token.type, LOWEST)

    def _expect_peek(self, t: TokenType) -> bool:
        if self.peek_token.type == t:
            self._next_token()
            return True
        self.errors.append(f"expected {t}, got {self.peek_token.type}")
        return False

    def parse_program(self) -> Program:
        program = Program()
        while self.cur_token.type != TokenType.EOF:
            stmt = self._parse_statement()
            if stmt is not None:
                program.statements.append(stmt)
            self._next_token()
        return program

    def _parse_statement(self):
        if self.cur_token.type == TokenType.LET:
            return self._parse_let_statement()
        elif self.cur_token.type == TokenType.RETURN:
            return self._parse_return_statement()
        else:
            return self._parse_expression_statement()

    def _parse_let_statement(self):
        stmt = LetStatement()
        if not self._expect_peek(TokenType.IDENT):
            return None
        stmt.name = Identifier(value=self.cur_token.literal)
        if not self._expect_peek(TokenType.ASSIGN):
            return None
        self._next_token()
        stmt.value = self._parse_expression(LOWEST)
        if self.peek_token.type == TokenType.SEMICOLON:
            self._next_token()
        return stmt

    def _parse_return_statement(self):
        stmt = ReturnStatement()
        self._next_token()
        stmt.return_value = self._parse_expression(LOWEST)
        if self.peek_token.type == TokenType.SEMICOLON:
            self._next_token()
        return stmt

    def _parse_expression_statement(self):
        stmt = ExpressionStatement()
        stmt.expression = self._parse_expression(LOWEST)
        if self.peek_token.type == TokenType.SEMICOLON:
            self._next_token()
        return stmt

    def _parse_expression(self, precedence: int):
        left = self._parse_prefix()
        if left is None:
            self.errors.append(f"no prefix parse function for {self.cur_token.type}")
            return None

        while (self.peek_token.type != TokenType.SEMICOLON
               and precedence < self._peek_precedence()):
            if self.peek_token.type not in (
                TokenType.PLUS, TokenType.MINUS, TokenType.SLASH,
                TokenType.ASTERISK, TokenType.PERCENT,
                TokenType.EQ, TokenType.NOT_EQ,
                TokenType.LT, TokenType.GT, TokenType.LT_EQ, TokenType.GT_EQ,
                TokenType.LPAREN, TokenType.LBRACKET,
            ):
                return left
            self._next_token()
            if self.cur_token.type == TokenType.LPAREN:
                left = self._parse_call_expression(left)
            elif self.cur_token.type == TokenType.LBRACKET:
                left = self._parse_index_expression(left)
            else:
                left = self._parse_infix_expression(left)
        return left

    def _parse_prefix(self):
        tt = self.cur_token.type
        if tt == TokenType.IDENT:
            return Identifier(value=self.cur_token.literal)
        elif tt == TokenType.INT:
            return IntegerLiteral(value=int(self.cur_token.literal))
        elif tt == TokenType.STRING:
            return StringLiteral(value=self.cur_token.literal)
        elif tt in (TokenType.TRUE, TokenType.FALSE):
            return BooleanLiteral(value=(tt == TokenType.TRUE))
        elif tt in (TokenType.BANG, TokenType.MINUS):
            return self._parse_prefix_expression()
        elif tt == TokenType.LPAREN:
            return self._parse_grouped_expression()
        elif tt == TokenType.IF:
            return self._parse_if_expression()
        elif tt == TokenType.FN:
            return self._parse_function_literal()
        elif tt == TokenType.LBRACKET:
            return self._parse_array_literal()
        return None

    def _parse_prefix_expression(self):
        expr = PrefixExpression(operator=self.cur_token.literal)
        self._next_token()
        expr.right = self._parse_expression(PREFIX)
        return expr

    def _parse_infix_expression(self, left):
        expr = InfixExpression(left=left, operator=self.cur_token.literal)
        prec = self._cur_precedence()
        self._next_token()
        expr.right = self._parse_expression(prec)
        return expr

    def _parse_grouped_expression(self):
        self._next_token()
        exp = self._parse_expression(LOWEST)
        if not self._expect_peek(TokenType.RPAREN):
            return None
        return exp

    def _parse_if_expression(self):
        expr = IfExpression()
        if not self._expect_peek(TokenType.LPAREN):
            return None
        self._next_token()
        expr.condition = self._parse_expression(LOWEST)
        if not self._expect_peek(TokenType.RPAREN):
            return None
        if not self._expect_peek(TokenType.LBRACE):
            return None
        expr.consequence = self._parse_block_statement()
        if self.peek_token.type == TokenType.ELSE:
            self._next_token()
            if not self._expect_peek(TokenType.LBRACE):
                return None
            expr.alternative = self._parse_block_statement()
        return expr

    def _parse_block_statement(self):
        block = BlockStatement()
        self._next_token()
        while self.cur_token.type != TokenType.RBRACE and self.cur_token.type != TokenType.EOF:
            stmt = self._parse_statement()
            if stmt is not None:
                block.statements.append(stmt)
            self._next_token()
        return block

    def _parse_function_literal(self):
        lit = FunctionLiteral()
        if not self._expect_peek(TokenType.LPAREN):
            return None
        lit.parameters = self._parse_function_parameters()
        if not self._expect_peek(TokenType.LBRACE):
            return None
        lit.body = self._parse_block_statement()
        return lit

    def _parse_function_parameters(self) -> list[Identifier]:
        params: list[Identifier] = []
        if self.peek_token.type == TokenType.RPAREN:
            self._next_token()
            return params
        self._next_token()
        params.append(Identifier(value=self.cur_token.literal))
        while self.peek_token.type == TokenType.COMMA:
            self._next_token()
            self._next_token()
            params.append(Identifier(value=self.cur_token.literal))
        if not self._expect_peek(TokenType.RPAREN):
            return []
        return params

    def _parse_call_expression(self, function):
        expr = CallExpression(function=function)
        expr.arguments = self._parse_expression_list(TokenType.RPAREN)
        return expr

    def _parse_array_literal(self):
        arr = ArrayLiteral()
        arr.elements = self._parse_expression_list(TokenType.RBRACKET)
        return arr

    def _parse_expression_list(self, end: TokenType) -> list:
        args = []
        if self.peek_token.type == end:
            self._next_token()
            return args
        self._next_token()
        args.append(self._parse_expression(LOWEST))
        while self.peek_token.type == TokenType.COMMA:
            self._next_token()
            self._next_token()
            args.append(self._parse_expression(LOWEST))
        if not self._expect_peek(end):
            return []
        return args

    def _parse_index_expression(self, left):
        expr = IndexExpression(left=left)
        self._next_token()
        expr.index = self._parse_expression(LOWEST)
        if not self._expect_peek(TokenType.RBRACKET):
            return None
        return expr
