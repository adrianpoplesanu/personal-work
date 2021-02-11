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
        pass

    def new_token(self):
        pass

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
        pass

    def read_number(self):
        pass

    def lookup_identifier(self):
        pass

    def skip_whitespace(self):
        pass

    def is_letter(self):
        pass

    def is_digit(self):
        pass


class Token(object):
    def __init__(self, token_type=None, literal=None):
        self.token_type = token_type
        self.literal = literal

    def __str__(self):
        return 'Token[token_type: ' + token_type_map[self.token_type] + '; literal: ' + self.literal + ']'
