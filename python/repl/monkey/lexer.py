class Lexer(object):
    def __init__(self, input='', position=0, readPosition=0, ch=''):
        self.input = input
        self.position = position
        self.readPosition = readPosition
        self.ch = ch
        self.readChar()

    def New(self, input=''):
        self.input = input
        self.position = 0
        self.readPosition = 0
        self.ch = ''
        self.readChar()

    def readChar(self):
        if self.readPosition >= len(self.input):
            self.ch = 0
        else:
            self.ch = self.input[self.readPosition]
        self.position = self.readPosition
        self.readPosition += 1

    def skipWhitespace(self):
        while self.ch == ' ' or self.ch == '\t' or self.ch == '\n' or self.ch == '\r':
            self.readChar()

    def isLetter(self, ch):
        return ('a' <= ch and ch <= 'z') or ('A' <= ch and ch <= 'Z') or ch == '_'

    def isDigit(self, ch):
        return '0' <= ch and ch <= '9'

    def readIdentifier(self):
        start = self.position
        while self.isLetter(self.ch):
            self.readChar()
        return self.input[start:self.position]

    def readNumber(self):
        start = self.position
        while self.isDigit(self.ch):
            self.readChar()
        return self.input[start:self.position]

    def LookupIdent(self, ident):
        if ident in Token.keywords:
            return Token.keywords[ident]
        return TokenType.IDENT

    def peekChar(self):
        if self.readPosition >= len(self.input):
            return 0
        else:
            return self.input[self.readPosition]

    def nextToken(self):
        #ch = self.ch
        tok = Token()
        self.skipWhitespace()
        if self.ch == '=':
            if self.peekChar() == '=':
                current_ch = self.ch
                self.readChar()
                literal = current_ch + self.ch
                tok = self.newToken(TokenType.EQ, literal)
            else:
                tok = self.newToken(TokenType.ASSIGN, self.ch)
        elif self.ch == '+':
            tok = self.newToken(TokenType.PLUS, self.ch)
        elif self.ch == '-':
            tok = self.newToken(TokenType.MINUS, self.ch)
        elif self.ch == "!":
            if self.peekChar() == '=':
                current_ch = self.ch
                self.readChar()
                literal = current_ch + self.ch
                tok = self.newToken(TokenType.NOT_EQ, literal)
            else:
                tok = self.newToken(TokenType.BANG, self.ch)
        elif self.ch == "/":
            tok = self.newToken(TokenType.SLASH, self.ch)
        elif self.ch == "*":
            tok = self.newToken(TokenType.ASTERISK, self.ch)
        elif self.ch == "<":
            tok = self.newToken(TokenType.LT, self.ch)
        elif self.ch == ">":
            tok = self.newToken(TokenType.GT, self.ch)
        elif self.ch == ',':
            tok = self.newToken(TokenType.COMMA, self.ch)
        elif self.ch == ';':
            tok = self.newToken(TokenType.SEMICOLON, self.ch)
        elif self.ch == '(':
            tok = self.newToken(TokenType.LPAREN, self.ch)
        elif self.ch == ')':
            tok = self.newToken(TokenType.RPAREN, self.ch)
        elif self.ch == '{':
            tok = self.newToken(TokenType.LBRACE, self.ch)
        elif self.ch == '}':
            tok = self.newToken(TokenType.RBRACE, self.ch)
        elif self.ch == 0:
            tok = self.newToken(TokenType.EOF, '')
        else:
            if self.isLetter(self.ch):
                tok.literal = self.readIdentifier()
                #tok.token_type = TokenType.IDENT
                tok.token_type = self.LookupIdent(tok.literal)
                return tok
            elif self.isDigit(self.ch):
                tok.literal = self.readNumber()
                tok.token_type = TokenType.INT
                return tok
            else:
                tok = self.newToken(TokenType.ILLEGAL, self.ch)
        self.readChar()
        return tok

    def newToken(self, token_type, literal):
        return Token(token_type, literal)


class TokenType(object):
    ILLEGAL = "ILLEGAL"
    EOF = "EOF"
    IDENT = "IDENT"
    INT = "INT"
    ASSIGN = "="
    PLUS = "+"
    MINUS = "-"
    BANG = "!"
    ASTERISK = "*"
    SLASH = "/"
    LT = "<"
    GT = ">"
    COMMA = ","
    SEMICOLON = ";"
    LPAREN = "("
    RPAREN = ")"
    LBRACE = "{"
    RBRACE = "}"
    FUNCTION = "FUNCTION"
    LET = "LET"
    TRUE = "TRUE"
    FALSE = "FALSE"
    IF = "IF"
    ELSE = "ELSE"
    RETURN = "RETURN"
    EQ = "=="
    NOT_EQ = "!="


class Token(object):

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

    keywords = {
        "fn": TokenType.FUNCTION,
        "let": TokenType.LET,
        "true": TokenType.TRUE,
        "false": TokenType.FALSE,
        "if": TokenType.IF,
        "else": TokenType.ELSE,
        "return": TokenType.RETURN
    }

    def __init__(self, token_type=None, literal=None):
        self.token_type = token_type
        self.literal = literal

    def __str__(self):
        return 'Token[type: ' + self.token_type_map[self.token_type] + ', literal: ' + self.literal + ']'
