package token;

import java.util.HashMap;

public class TokenTypeConverter {
    public static HashMap<TokenType, String> tokenTypeMap = new HashMap<TokenType, String>() {
        {
            put(TokenType.UNDEFINED, "UNDEFINED");
            put(TokenType.SUM, "SUM");
            put(TokenType.MINUS, "MINUS");
            put(TokenType.MULTIPLY, "MULTIPLY");
            put(TokenType.DIVIDE, "DIVIDE");
        }
    };
}
