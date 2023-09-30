package ro.adrianus.prototype.token;

import java.util.HashMap;

public enum TokenTypeEnum {
    ILLEGAL,
    EOF,
    INT,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE;

    private static HashMap<String, TokenTypeEnum> keywords = new HashMap<String, TokenTypeEnum>() {
        private static final long serialVersionUID = 1L;
        {
            put("let", TokenTypeEnum.ILLEGAL);
            put("return", TokenTypeEnum.ILLEGAL);
            put("func", TokenTypeEnum.ILLEGAL);
            put("if", TokenTypeEnum.ILLEGAL);
            put("else", TokenTypeEnum.ILLEGAL);
        }
    };

    private static HashMap<TokenTypeEnum, String> mapToString = new HashMap<TokenTypeEnum, String>() {
        private static final long serialVersionUID = 1L;
        {
            put(TokenTypeEnum.ILLEGAL, "ILLEGAL");
            put(TokenTypeEnum.EOF, "EOF");
            put(TokenTypeEnum.PLUS, "PLUS");
            put(TokenTypeEnum.MINUS, "MINUS");
            put(TokenTypeEnum.MULTIPLY, "MULTIPLY");
            put(TokenTypeEnum.DIVIDE, "DIVIDE");
        }
    };

    public static TokenTypeEnum convertToKeyword(String identifier) {
        return keywords.get(identifier);
    }

    public static String convertToString(TokenTypeEnum type) {
        return mapToString.get(type);
    }
}
