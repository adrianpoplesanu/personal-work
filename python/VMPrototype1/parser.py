from lexer import Lexer
from token_type import TokenType


class Parser:
    def __init__(self):
        self.source = None
        self.lexer = Lexer()
        self.current_token = None
        self.peek_token = None
        self.prefix_parse_fns = {}
        self.infix_parse_fns = {}
        self.prefix_parse_fns[TokenType.IDENT] = self.parse_identifier

    def load(self, source):
        self.source = source
        self.lexer.load(source)
        self.next_token()
        self.next_token()

    def build_program_statements(self, program):
        while self.current_token.token_type != TokenType.EOF:
            self.next_token()
            pass

    def next_token(self):
        self.current_token = self.peek_token
        self.peek_token = self.lexer.next_token()

    def current_token_id(self, token_type : TokenType):
        return self.current_token.token_type == token_type

    def peek_token_is(self, token_type: TokenType):
        return self.peek_token.token_type == token_type

    def parse_statement(self):
        pass

    def parse_identifier(self):
        pass

    def parse_expressions_statement(self):
        pass

    def parse_expression(self):
        pass
