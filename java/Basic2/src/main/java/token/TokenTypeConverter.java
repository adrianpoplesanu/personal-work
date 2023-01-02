package token;

import java.util.HashMap;

public class TokenTypeConverter {
    private static final HashMap<TokenTypeEnum, String> tokenTypeMap = new HashMap<TokenTypeEnum, String>() {
        {
            put(TokenTypeEnum.ILLEGAL, "ILLEGAL");
            put(TokenTypeEnum.EOF, "EOF");
            put(TokenTypeEnum.PLUS, "PLUS");
            put(TokenTypeEnum.MINUS, "MINUS");
            put(TokenTypeEnum.MULTIPLY, "MULTIPLY");
            put(TokenTypeEnum.DIVIDE, "DIVIDE");
            put(TokenTypeEnum.INT, "INT");
        }
    };

    public static String covertToken(TokenTypeEnum tte) {
        return tokenTypeMap.get(tte);
    }
}
