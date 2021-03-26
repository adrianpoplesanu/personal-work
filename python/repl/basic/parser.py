from ast import LetStatement
from token_type import TokenType


class Parser(object):
    def __init__(self, lexer):
        self.lexer = lexer
        self.current_token = None
        self.peek_token = None

    def reset(self, source):
        self.lexer.new(source=source)
        self.next_token()
        self.next_token()

    def register_prefix(self):
        pass

    def register_inflix(self):
        pass

    def next_token(self):
        self.current_token = self.peek_token
        self.peek_token = self.lexer.next_token()

    def current_token_is(self, token_type):
        return self.current_token.token_type == token_type

    def peek_token_is(self, token_type):
        return self.peek_token.token_type == token_type

    def expect_peek(self, token_type):
        if self.peek_token_is(token_type):
            self.next_token()
            return True
        return False

    def build_program_statements(self, program):
        # this returns a program based on the source of the lexer, this is better naming for this method
        # this is the old ParseProgram functions
        while self.current_token.token_type != TokenType.EOF:
            statement = self.parse_statement()
            if statement:
                program.statements.append(statement)
            self.next_token()

    def parse_statement(self):
        if self.current_token.token_type == TokenType.LET:
            return self.parse_let_statement()
        if self.current_token.token_type == TokenType.RETURN:
            return self.parse_return_statement()
        if self.current_token.token_type == TokenType.WHILE:
            return self.parse_while_statement()
        return self.parse_expression_statement()

    def parse_let_statement(self):
        let_statement = LetStatement()
        #print let_statement
        return self.current_token

    def parse_return_statement(self):
        return self.current_token

    def parse_while_statement(self):
        # this might be different in the final product
        return self.current_token

    def parse_expression_statement(self):
        return self.current_token

    def parse_expression(self, precedence):
        pass

    def parse_identifier(self):
        pass

    def parse_integer_literal(self):
        pass

    def parse_prefix_expression(self):
        pass

    def peek_precedence(self):
        pass

    def current_precedence(self):
        pass

    def parse_inflix_expression(self, left):
        pass


class ParsingPrecendece(object):
    LOWEST = 1
    EQUALS = 2
    LESSGREATER = 3
    SUM = 4
    PRODUCT = 5
    PREFIX = 6
    CALL = 7