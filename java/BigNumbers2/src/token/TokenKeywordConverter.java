package token;

import java.util.HashMap;

public class TokenKeywordConverter {
    private static HashMap<String, TokenType> keywordsMap = new HashMap<String, TokenType>() {
        {
            put("if", TokenType.IF);
            put("true", TokenType.TRUE);
            put("false", TokenType.FALSE);
            put("let", TokenType.LET);
            put("else", TokenType.ELSE);
            put("and", TokenType.AND);
            put("or", TokenType.OR);
        }
    };

    public static TokenType convertKeyword(String literal) {
        return keywordsMap.get(literal);
    }

    public static boolean checkKeyword(String literal) {
        return keywordsMap.containsKey(literal);
    }
}
