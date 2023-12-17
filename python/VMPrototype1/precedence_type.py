from token_type import TokenType


class PrecedenceType:
    LOWEST = 0
    SUM = 6
    PRODUCT = 7


precedences = {
    TokenType.PLUS: PrecedenceType.SUM,
    TokenType.MINUS: PrecedenceType.SUM,
    TokenType.SLASH: PrecedenceType.PRODUCT,
    TokenType.ASTERISK: PrecedenceType.PRODUCT,
}
