package parser;

import token.TokenType;

import java.util.HashMap;

public class PrecedenceTypeConverter {
    private HashMap<TokenType, PrecedenceType> precedenceMap = new HashMap<TokenType, PrecedenceType>() {
        {
            put(TokenType.SUM, PrecedenceType.SUM);
            put(TokenType.MINUS, PrecedenceType.SUM);
            put(TokenType.EQ, PrecedenceType.EQUALS);
            put(TokenType.NON_EQ, PrecedenceType.EQUALS);
            put(TokenType.MULTIPLY, PrecedenceType.MULTIPLY);
            put(TokenType.DIVIDE, PrecedenceType.MULTIPLY);
            put(TokenType.LPAREN, PrecedenceType.CALL);
            put(TokenType.AND, PrecedenceType.CONDITIONAL);
            put(TokenType.OR, PrecedenceType.CONDITIONAL);
            put(TokenType.GT, PrecedenceType.LESSGREATER);
            put(TokenType.LT, PrecedenceType.LESSGREATER);
            put(TokenType.GTE, PrecedenceType.LESSGREATER);
            put(TokenType.LTE, PrecedenceType.LESSGREATER);
            put(TokenType.ASSIGN, PrecedenceType.ASSIGN);
        }
    };
}
