package token;

import java.util.HashMap;

public class TokenKeywordConverter {
    public static HashMap<TokenType, String> keywordsMap = new HashMap<TokenType, String>() {
        {
            put(TokenType.IF, "IF");
            put(TokenType.TRUE, "TRUE");
            put(TokenType.FALSE, "FALSE");
            put(TokenType.LET, "LET");
        }
    };
}
