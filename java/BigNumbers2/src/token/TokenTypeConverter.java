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
        }
    };
}
