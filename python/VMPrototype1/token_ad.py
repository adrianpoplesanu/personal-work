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
    TokenType.WHILE: "WHILE",
    TokenType.NULL: "NULL",
    TokenType.ASSIGN: 'ASSIGN',
    TokenType.DEF: "DEF",
    TokenType.DOT: "DOT"
}

keywords_map = {
    "let": TokenType.LET,
    "return": TokenType.RETURN,
    "func": TokenType.FUNC,
    "if": TokenType.IF,
    "else": TokenType.ELSE,
    "true": TokenType.TRUE,
    "false": TokenType.FALSE,
    "while": TokenType.WHILE,
    "def": TokenType.DEF,
    "fun": TokenType.FUN,
    "function": TokenType.FUNCTION,
    "method": TokenType.METHOD,
    "null": TokenType.NULL,
    "class": TokenType.CLASS,
    "this": TokenType.THIS,
    "and": TokenType.AND,
    "or": TokenType.OR,
    "for": TokenType.FOR,
    "break": TokenType.BREAK,
    "continue": TokenType.CONTINUE,
    "super": TokenType.SUPER,
    "dot": TokenType.DOT
}


class Token:
    def __init__(self, token_type: TokenType, literal: str):
        self.token_type = token_type
        self.literal = literal

    def __str__(self):
        return "Token [type: " + token_type_map[self.token_type] + ", literal: " + self.literal + "]"
