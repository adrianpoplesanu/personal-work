from enum import Enum, auto


class TokenType(Enum):
    ILLEGAL = auto()
    EOF = auto()

    IDENT = auto()
    INT = auto()
    STRING = auto()

    ASSIGN = auto()
    PLUS = auto()
    MINUS = auto()
    BANG = auto()
    ASTERISK = auto()
    SLASH = auto()
    PERCENT = auto()

    LT = auto()
    GT = auto()
    EQ = auto()
    NOT_EQ = auto()
    LT_EQ = auto()
    GT_EQ = auto()

    COMMA = auto()
    SEMICOLON = auto()

    LPAREN = auto()
    RPAREN = auto()
    LBRACE = auto()
    RBRACE = auto()
    LBRACKET = auto()
    RBRACKET = auto()

    LET = auto()
    FN = auto()
    TRUE = auto()
    FALSE = auto()
    IF = auto()
    ELSE = auto()
    RETURN = auto()


KEYWORDS = {
    "let": TokenType.LET,
    "fn": TokenType.FN,
    "true": TokenType.TRUE,
    "false": TokenType.FALSE,
    "if": TokenType.IF,
    "else": TokenType.ELSE,
    "return": TokenType.RETURN,
}


class Token:
    __slots__ = ("type", "literal")

    def __init__(self, type: TokenType, literal: str):
        self.type = type
        self.literal = literal

    def __repr__(self):
        return f"Token({self.type}, {self.literal!r})"
