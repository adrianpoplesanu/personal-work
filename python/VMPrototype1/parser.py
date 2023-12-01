from lexer import Lexer
from token_type import TokenType


class Parser:
    def __init__(self):
        self.source = None
        self.lexer = Lexer()
        self.prefix_parse_fns = {}
        self.infix_parse_fns = {}
        self.prefix_parse_fns[TokenType.IDENT] = self.parse_identifier

    def load(self, source):
        self.source = source

    def build_program_statements(self, program):
        pass

    def parse_statement(self):
        pass

    def parse_identifier(self):
        pass

    def parse_expressions_statement(self):
        pass

    def parse_expression(self):
        pass
