package token;

import java.util.HashMap;

public class TokenTypeConverter {
    private static HashMap<TokenType, String> tokenTypeMap = new HashMap<TokenType, String>() {
        {
            put(TokenType.UNDEFINED, "UNDEFINED");
            put(TokenType.SUM, "SUM");
            put(TokenType.MINUS, "MINUS");
            put(TokenType.MULTIPLY, "MULTIPLY");
            put(TokenType.DIVIDE, "DIVIDE");
            put(TokenType.BIG_NUMBER, "BIG_NUMBER");
            put(TokenType.ASSIGN, "ASSIGN");
            put(TokenType.LPAREN, "LPAREN");
            put(TokenType.RPAREN, "RPAREN");
            put(TokenType.SEMICOLON, "SEMICOLON");
            put(TokenType.IF, "IF");
            put(TokenType.TRUE, "IF");
            put(TokenType.FALSE, "IF");
            put(TokenType.LET, "IF");
            put(TokenType.DOT, "DOT");
            put(TokenType.GT, "GT");
            put(TokenType.LT, "LT");
            put(TokenType.GTE, "GTE");
            put(TokenType.LTE, "LTE");
            put(TokenType.EOF, "EOF");
            put(TokenType.ELSE, "ELSE");
            put(TokenType.LBRACKET, "LBRACKET");
            put(TokenType.RBRACKET, "RBRACKET");
            put(TokenType.EQ, "EQ");
            put(TokenType.NON_EQ, "NON_EQ");
            put(TokenType.AND, "AND");
            put(TokenType.OR, "OR");
        }
    };

    public static String convertTokenType(TokenType key) {
        return tokenTypeMap.get(key);
    }
}
