from token_type import TokenType


keywords = {
    "let": TokenType.LET,
    "true": TokenType.TRUE,
    "false": TokenType.FALSE,
    "if": TokenType.IF,
    "else": TokenType.ELSE,
    "while": TokenType.WHILE,
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
    TokenType.WHILE: "WHILE",
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
        skip_last_read = False
        token = Token()
        self.skip_whitespace()
        if self.ch == '=':
            if self.peek_char() == '=':
                literal = self.ch + self.peek_char()
                self.read_char()
                token = self.new_token(TokenType.EQ, literal)
            else:
                literal = self.ch
                token = self.new_token(TokenType.ASSIGN, literal)
        elif self.ch == '+':
            literal = self.ch
            token = self.new_token(TokenType.PLUS, literal)
        elif self.ch == '-':
            literal = self.ch
            token = self.new_token(TokenType.MINUS, literal)
        elif self.ch == '*':
            literal = self.ch
            token = self.new_token(TokenType.ASTERISK, literal)
        elif self.ch == '/':
            literal = self.ch
            token = self.new_token(TokenType.SLASH, literal)
        elif self.ch == '{':
            literal = self.ch
            token = self.new_token(TokenType.LBRACE, literal)
        elif self.ch == '}':
            literal = self.ch
            token = self.new_token(TokenType.RBRACE, literal)
        elif self.ch == '(':
            literal = self.ch
            token = self.new_token(TokenType.LPAREN, literal)
        elif self.ch == ')':
            literal = self.ch
            token = self.new_token(TokenType.RPAREN, literal)
        elif self.ch == '>':
            literal = self.ch
            token = self.new_token(TokenType.GT, literal)
        elif self.ch == '<':
            literal = self.ch
            token = self.new_token(TokenType.LT, literal)
        elif self.ch == ',':
            literal = self.ch
            token = self.new_token(TokenType.COMMA, literal)
        elif self.ch == '!':
            if self.peek_char() == '=':
                literal = self.ch + self.peek_char()
                self.read_char()
                token = self.new_token(TokenType.NOT_EQ, literal)
            else:
                literal = self.ch
                token = self.new_token(TokenType.BANG, literal)
        elif self.ch == ';':
            literal = self.ch
            token = self.new_token(TokenType.SEMICOLON, literal)
        elif self.ch == 0:
            literal = ''
            token = self.new_token(TokenType.EOF, literal)
        else:
            if self.is_letter():
                literal = self.read_identifier()
                token_type = self.lookup_identifier(literal)
                token = self.new_token(token_type, literal)
                skip_last_read = True
            elif self.is_digit():
                literal = self.read_number()
                token = self.new_token(TokenType.INT, literal)
                skip_last_read = True
            else:
                literal = self.ch
                token = self.new_token(TokenType.ILLEGAL, self.ch)
        if not skip_last_read:
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
