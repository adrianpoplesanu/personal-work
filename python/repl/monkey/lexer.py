class Lexer(object):
    def __init__(self, input, position=0, readPosition=0, ch=''):
        self.input = input
        self.position = position
        self.readPosition = readPosition
        self.ch = ch
        self.readChar()

    def readChar(self):
        if self.readPosition >= len(self.input):
            self.ch = 0
        else:
            self.ch = self.input[self.readPosition]
        self.position = self.readPosition
        self.readPosition += 1

    def nextToken(self, ch):
        tok = None
        if self.ch == '=':
            tok = self.newToken(Token.ASSIGN, self.ch)
        elif self.ch == '+':
            tok = self.newToken(Token.PLUS, self.ch)
        elif self.ch == ',':
            tok = self.newToken(Token.COMMA, self.ch)
        elif self.ch == ';':
            tok = self.newToken(Token.SEMICOLON, self.ch)
        elif self.ch == '(':
            tok = self.newToken(Token.LPAREN, self.ch)
        elif self.ch == ')':
            tok = self.newToken(Token.RPAREN, self.ch)
        elif self.ch == '{':
            tok = self.newToken(Token.LBRACE, self.ch)
        elif self.ch == '}':
            tok = self.newToken(Token.RBRACE, self.ch)
        self.readChar()
        return tok

    def newToken(self, type, literal):
        return Token(type, literal)


class Token(object):

    ILLEGAL = "ILLEGAL"
    EOF = "EOF"
    IDENT = "IDENT"
    INT = "INT"
    ASSIGN = "="
    PLUS = "+"
    COMMA = ","
    SEMICOLON = ";"
    LPAREN = "("
    RPAREN = ")"
    LBRACE = "{"
    RBRACE = "}"
    FUNCTION = "FUNCTION"
    LET = "LET"

    def __init__(self, type, literal):
        self.type = type
        self.literal = literal

    def __str__(self):
        return 'aaa'
