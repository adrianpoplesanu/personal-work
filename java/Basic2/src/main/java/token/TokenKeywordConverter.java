package token;

import java.util.HashMap;
import java.util.Map;

public class TokenKeywordConverter {
    private static final Map<String, TokenTypeEnum> keywordsMap = new HashMap<String, TokenTypeEnum>() {
        {
            put("to do", null);
        }
    };

    public static TokenTypeEnum lookupKeyword(String tokenLiteral) {
        return keywordsMap.get(tokenLiteral);
    }
}
