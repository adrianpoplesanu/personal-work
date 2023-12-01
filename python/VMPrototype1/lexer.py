from token import Token, keywords_map
from token_type import TokenType


def lookup_ident(ident: str) -> TokenType:
    if ident in keywords_map:
        return keywords_map[ident]
    return TokenType.ILLEGAL


class Lexer:
    def __init__(self, position=0, read_position=0, source=''):
        self.position = position
        self.read_position = read_position
        self.ch = ''
        self.source = source
        self.read_char()

    def load(self, source=''):
        self.position = 0
        self.read_position = 0
        self.ch = ''
        self.source = source
        self.read_char()

    def read_char(self):
        if self.read_position < len(self.source):
            self.ch = self.source[self.read_position]
        else:
            self.ch = 0
        self.position = self.read_position
        self.read_position += 1

    def next_token(self) -> Token:
        token = Token(TokenType.ILLEGAL, "")
        self.skip_whitespaces()
        skip_read_char = False
        if self.ch == '+':
            token.token_type = TokenType.PLUS
            token.literal = '+'
        elif self.ch == '-':
            token.token_type = TokenType.MINUS
            token.literal = '-'
        else:
            pass
        if not skip_read_char:
            self.read_char()
        return token

    def skip_whitespaces(self):
        while self.ch == ' ' or self.ch == '\t' or self.ch == '\r' or self.ch == '\n':
            self.read_char()

    def is_letter(self) -> bool:
        if self.ch == 0:
            return False
        return ('a' <= self.ch <= 'z') or ('A' <= self.ch <= 'Z') or '_' == self.ch

    def is_digit(self) -> bool:
        if self.ch == 0:
            return False
        return '0' <= self.ch <= '9'

    def read_ident(self):
        pass

    def read_numbers(self):
        pass

    def read_double_quotes_string(self):
        pass

    def read_single_quotes_string(self):
        pass

    def peek_char(self):
        pass

    def is_float_dot(self):
        pass
