package token;

import java.util.HashMap;

public class TokenKeywordConverter {
    private static HashMap<String, TokenType> keywordsMap = new HashMap<String, TokenType>() {
        {
            put("IF", TokenType.IF);
            put("TRUE", TokenType.TRUE);
            put("FALSE", TokenType.FALSE);
            put("LET", TokenType.LET);
        }
    };

    public static TokenType convertKeyword(String literal) {
        return keywordsMap.get(literal);
    }

    public static boolean checkKeyword(String literal) {
        return keywordsMap.containsKey(literal);
    }
}
