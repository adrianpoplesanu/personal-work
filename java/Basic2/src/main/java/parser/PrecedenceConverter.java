package parser;

import token.TokenTypeEnum;

import java.util.HashMap;
import java.util.Map;

public class PrecedenceConverter {
    private static final Map<TokenTypeEnum, PrecedenceTypeEnum> precedenceMap = new HashMap<TokenTypeEnum, PrecedenceTypeEnum>() {
        {
            put(TokenTypeEnum.PLUS, PrecedenceTypeEnum.SUM);
            put(TokenTypeEnum.MINUS, PrecedenceTypeEnum.SUM);
            put(TokenTypeEnum.MULTIPLY, PrecedenceTypeEnum.MULTIPLY);
            put(TokenTypeEnum.DIVIDE, PrecedenceTypeEnum.MULTIPLY);
        }
    };

    public static PrecedenceTypeEnum convertTokenTypeToPrecedence(TokenTypeEnum tte) {
        return precedenceMap.get(tte);
    }

    public static boolean hasPrecedenceBind(TokenTypeEnum tte) {
        if (precedenceMap.containsKey(tte)) {
            return true;
        }
        return false;
    }
}
