from token import Token
from token_type import TokenType


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
        self.skip_whitespaces()
        return None

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
