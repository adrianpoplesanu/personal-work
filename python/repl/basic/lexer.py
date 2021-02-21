from token_type import TokenType


keywords = {
    "let": TokenType.LET,
    "true": TokenType.TRUE,
    "false": TokenType.FALSE,
    "if": TokenType.IF,
    "else": TokenType.ELSE,
}

token_type_map = {
    TokenType.ASSIGN: "ASSIGN",
    TokenType.ILLEGAL: "ILLEGAL",
    TokenType.EOF: "EOF",
    TokenType.IDENT: "IDENT",
    TokenType.INT: "INT",
    TokenType.PLUS: "PLUS",
    TokenType.MINUS: "MINUS",
    TokenType.BANG: "BANG",
    TokenType.ASTERISK: "ASTERISK",
    TokenType.SLASH: "SLASH",
    TokenType.LT: "LT",
    TokenType.GT: "GT",
    TokenType.COMMA: "COMMA",
    TokenType.SEMICOLON: "SEMICOLON",
    TokenType.LPAREN: "LPAREN",
    TokenType.RPAREN: "RPAREN",
    TokenType.LBRACE: "LBRACE",
    TokenType.RBRACE: "RBRACE",
    TokenType.FUNCTION: "FUNCTION",
    TokenType.LET: "LET",
    TokenType.TRUE: "TRUE",
    TokenType.FALSE: "FALSE",
    TokenType.IF: "IF",
    TokenType.ELSE: "ELSE",
    TokenType.RETURN: "RETURN",
    TokenType.EQ: "EQ",
    TokenType.NOT_EQ: "NOT_EQ"
}


class Lexer(object):
    def __init__(self):
        self.source = ''
        self.position = 0
        self.read_position = 0
        self.ch = ''

    def new(self, source):
        self.source = source
        self.position = 0
        self.read_position = 0
        self.ch = ''
        self.read_char()

    def next_token(self):
        token = Token()
        self.skip_whitespace()
        if self.ch == '=':
            token = self.new_token(TokenType.ILLEGAL, self.ch)
        elif self.ch == ';':
            token = self.new_token(TokenType.ILLEGAL, self.ch)
        elif self.ch == 0:
            token = self.new_token(TokenType.EOF, '')
        else:
            if self.is_letter:
                token = self.new_token(TokenType.ILLEGAL, self.ch)
            elif self.is_number:
                token = self.new_token(TokenType.ILLEGAL, self.ch)
            else:
                token = self.new_token(TokenType.ILLEGAL, self.ch)
        self.read_char()
        return token 

    def new_token(self, token_type, literal):
        return Token(token_type, literal)

    def read_char(self):
        if self.read_position >= len(self.source):
            self.ch = 0
        else:
            self.ch = self.source[self.read_position]
        self.position = self.read_position
        self.read_position += 1

    def peek_char(self):
        if self.read_position >= len(self.source):
            return 0
        else:
            return self.source[self.read_position]

    def read_identifier(self):
        start = self.position
        while self.is_letter():
            self.read_char()
        return self.source[start:self.position]

    def read_number(self):
        start = self.position
        while self.is_digit():
            self.read_char()
        return self.source[start:self.position]

    def lookup_identifier(self, ident):
        if ident in keywords:
            return keywords[ident]
        return TokenType.IDENT

    def skip_whitespace(self):
        while self.ch == ' ' or self.ch == '\t' or self.ch == '\n' or self.ch == '\r':
            self.read_char()

    def is_letter(self):
        return ('a' <= self.ch and self.ch <= 'z') or ('A' <= self.ch and self.ch <= 'Z') or self.ch == '_'

    def is_digit(self):
        return '0' <= self.ch and self.ch <= '9' 


class Token(object):
    def __init__(self, token_type=None, literal=None):
        self.token_type = token_type
        self.literal = literal

    def __str__(self):
        return 'Token[token_type: ' + token_type_map[self.token_type] + '; literal: ' + self.literal + ']'
