from token_type import TokenType

token_type_map = {
    TokenType.ILLEGAL: "ILLEGAL",
    TokenType.AND: "AND"
}

keywords_map = {
    "and": TokenType.AND
}


class Token:
    def __init__(self, token_type: TokenType, literal: str):
        self.token_type = token_type
        self.literal = literal

    def __str__(self):
        return "Token [type: " + token_type_map[self.token_type] + ", literal: " + self.literal + "]"
