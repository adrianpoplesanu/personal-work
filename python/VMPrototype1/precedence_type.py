from token_type import TokenType


class PrecedenceType:
    LOWEST = 1
    ASSIGN = 2
    EQUALS = 3
    LESSGREATER = 5
    SUM = 6
    PRODUCT = 7
    PREFIX = 9


precedences = {
    TokenType.ASSIGN: PrecedenceType.ASSIGN,
    TokenType.PLUS: PrecedenceType.SUM,
    TokenType.MINUS: PrecedenceType.SUM,
    TokenType.SLASH: PrecedenceType.PRODUCT,
    TokenType.ASTERISK: PrecedenceType.PRODUCT,
    TokenType.EQ: PrecedenceType.EQUALS,
    TokenType.NOT_EQ: PrecedenceType.EQUALS,
    TokenType.GT: PrecedenceType.LESSGREATER,
    TokenType.LT: PrecedenceType.LESSGREATER,
    TokenType.GTE: PrecedenceType.LESSGREATER,
    TokenType.LTE: PrecedenceType.LESSGREATER
}
