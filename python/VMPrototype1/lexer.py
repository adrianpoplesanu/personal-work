from token_ad import Token, keywords_map
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
        if self.ch == 0:
            token.token_type = TokenType.EOF
            token.literal = ''
        elif self.ch == '+':
            token.token_type = TokenType.PLUS
            token.literal = '+'
        elif self.ch == '-':
            token.token_type = TokenType.MINUS
            token.literal = '-'
        elif self.ch == '*':
            token.token_type = TokenType.ASTERISK
            token.literal = '*'
        elif self.ch == '/':
            token.token_type = TokenType.SLASH
            token.literal = '/'
        elif self.ch == '(':
            token.token_type = TokenType.LPAREN
            token.literal = '('
        elif self.ch == ')':
            token.token_type = TokenType.RPAREN
            token.literal = ')'
        elif self.ch == '<':
            if self.peek_char() == '=':
                self.read_char()
                token.token_type = TokenType.LTE
                token.literal = '<='
            else:
                token.token_type = TokenType.LT
                token.literal = '<'
        elif self.ch == '>':
            if self.peek_char() == '=':
                self.read_char()
                token.token_type = TokenType.GTE
                token.literal = '>='
            else:
                token.token_type = TokenType.GT
                token.literal = '>'
        elif self.ch == '=':
            if self.peek_char() == '=':
                self.read_char()
                token.token_type = TokenType.EQ
                token.literal = '=='
            else:
                token.token_type = TokenType.ASSIGN
                token.literal = '='
        elif self.ch == '!':
            if self.peek_char() == '=':
                self.read_char()
                token.token_type = TokenType.NOT_EQ
                token.literal = '!='
            else:
                token.token_type = TokenType.BANG
                token.literal = '!'
        else:
            if self.is_letter():
                token.literal = self.read_ident()
                token.token_type = lookup_ident(token.literal)
                skip_read_char = True
            elif self.is_digit():
                token.literal = self.read_number()
                if '.' in token.literal:
                    token.token_type = TokenType.FLOAT
                else:
                    token.token_type = TokenType.INT
                skip_read_char = True
            else:
                token.token_type = TokenType.ILLEGAL
                token.literal = ''
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

    def read_ident(self) -> str:
        start = self.position
        while self.is_letter() or self.is_digit():
            self.read_char()
        return self.source[start:self.position]

    def read_number(self) -> str:
        start = self.position
        while self.is_digit():
            self.read_char()
        if self.is_float_dot():
            self.read_char()
            while self.is_digit():
                self.read_char()
        return self.source[start:self.position]

    def read_double_quotes_string(self):
        pass

    def read_single_quotes_string(self):
        pass

    def peek_char(self):
        if self.read_position >= len(self.source):
            return 0
        return self.source[self.read_position]

    def is_float_dot(self) -> bool:
        return self.ch == '.'
