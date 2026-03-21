from tokens import Token, TokenType, KEYWORDS


class Lexer:
    def __init__(self, source: str):
        self.source = source
        self.pos = 0
        self.ch = ""
        self._read_char()

    def _read_char(self):
        if self.pos >= len(self.source):
            self.ch = "\0"
        else:
            self.ch = self.source[self.pos]
        self.pos += 1

    def _peek_char(self) -> str:
        if self.pos >= len(self.source):
            return "\0"
        return self.source[self.pos]

    def _skip_whitespace(self):
        while self.ch in (" ", "\t", "\n", "\r"):
            self._read_char()

    def _read_identifier(self) -> str:
        start = self.pos - 1
        while self.ch.isalpha() or self.ch == "_" or self.ch.isdigit():
            self._read_char()
        return self.source[start : self.pos - 1]

    def _read_number(self) -> str:
        start = self.pos - 1
        while self.ch.isdigit():
            self._read_char()
        return self.source[start : self.pos - 1]

    def _read_string(self) -> str:
        self._read_char()  # skip opening quote
        start = self.pos - 1
        while self.ch != '"' and self.ch != "\0":
            self._read_char()
        value = self.source[start : self.pos - 1]
        self._read_char()  # skip closing quote
        return value

    def next_token(self) -> Token:
        self._skip_whitespace()
        ch = self.ch

        if ch == "=":
            if self._peek_char() == "=":
                self._read_char()
                self._read_char()
                return Token(TokenType.EQ, "==")
            self._read_char()
            return Token(TokenType.ASSIGN, "=")
        elif ch == "+":
            self._read_char()
            return Token(TokenType.PLUS, "+")
        elif ch == "-":
            self._read_char()
            return Token(TokenType.MINUS, "-")
        elif ch == "!":
            if self._peek_char() == "=":
                self._read_char()
                self._read_char()
                return Token(TokenType.NOT_EQ, "!=")
            self._read_char()
            return Token(TokenType.BANG, "!")
        elif ch == "*":
            self._read_char()
            return Token(TokenType.ASTERISK, "*")
        elif ch == "/":
            self._read_char()
            return Token(TokenType.SLASH, "/")
        elif ch == "%":
            self._read_char()
            return Token(TokenType.PERCENT, "%")
        elif ch == "<":
            if self._peek_char() == "=":
                self._read_char()
                self._read_char()
                return Token(TokenType.LT_EQ, "<=")
            self._read_char()
            return Token(TokenType.LT, "<")
        elif ch == ">":
            if self._peek_char() == "=":
                self._read_char()
                self._read_char()
                return Token(TokenType.GT_EQ, ">=")
            self._read_char()
            return Token(TokenType.GT, ">")
        elif ch == ",":
            self._read_char()
            return Token(TokenType.COMMA, ",")
        elif ch == ";":
            self._read_char()
            return Token(TokenType.SEMICOLON, ";")
        elif ch == "(":
            self._read_char()
            return Token(TokenType.LPAREN, "(")
        elif ch == ")":
            self._read_char()
            return Token(TokenType.RPAREN, ")")
        elif ch == "{":
            self._read_char()
            return Token(TokenType.LBRACE, "{")
        elif ch == "}":
            self._read_char()
            return Token(TokenType.RBRACE, "}")
        elif ch == "[":
            self._read_char()
            return Token(TokenType.LBRACKET, "[")
        elif ch == "]":
            self._read_char()
            return Token(TokenType.RBRACKET, "]")
        elif ch == '"':
            return Token(TokenType.STRING, self._read_string())
        elif ch == "\0":
            return Token(TokenType.EOF, "")
        elif ch.isalpha() or ch == "_":
            ident = self._read_identifier()
            token_type = KEYWORDS.get(ident, TokenType.IDENT)
            return Token(token_type, ident)
        elif ch.isdigit():
            return Token(TokenType.INT, self._read_number())
        else:
            self._read_char()
            return Token(TokenType.ILLEGAL, ch)
