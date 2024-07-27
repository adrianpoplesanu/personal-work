from token_type import TokenType

token_type_map = {
    TokenType.ILLEGAL: "ILLEGAL",
    TokenType.INT: "INT",
    TokenType.IDENT: "IDENT",
    TokenType.PLUS: "PLUS",
    TokenType.MINUS: "MINUS",
    TokenType.ASTERISK: "ASTERISK",
    TokenType.SLASH: "SLASH",
    TokenType.AND: "AND",
    TokenType.OR: "OR",
    TokenType.TRUE: "TRUE",
    TokenType.FALSE: "FALSE",
    TokenType.IF: "IF",
    TokenType.WHILE: "WHILE"
}

keywords_map = {
    "let": TokenType.LET,
    "return": TokenType.RETURN,
    "fun": TokenType.FUNCTION,
    "def": TokenType.DEF,
    "if": TokenType.IF,
    "else": TokenType.ELSE,
    "true": TokenType.TRUE,
    "false": TokenType.FALSE,
    "while": TokenType.WHILE,
    "for": TokenType.FOR,
    "and": TokenType.AND
}


class Token:
    def __init__(self, token_type: TokenType, literal: str):
        self.token_type = token_type
        self.literal = literal

    def __str__(self):
        return "Token [type: " + token_type_map[self.token_type] + ", literal: " + self.literal + "]"
