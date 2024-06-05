package ro.adrianus.prototype.token;

import java.util.HashMap;

public enum TokenTypeEnum {
    ILLEGAL,
    EOF,
    INT,
    PLUS,
    SUB,
    MULTIPLY,
    DIVIDE,
    IDENT,
    ASSIGN,
    LET,
    RETURN,
    FUNCTION,
    DEF,
    IF,
    ELSE,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    TRUE,
    FALSE,
    WHILE,
    FOR,
    BREAK,
    CONTINUE,
    SINGLECOMMENT,
    MULTICOMMENT,
    SEMICOLON,
    GT,
    LT,
    GTE,
    LTE,
    EQUALS,
    NOT_EQUALS,
    CLASS,
    THIS,
    SUPER,
    PLUSPLUS,
    MINUSMINUS,
    PLUS_EQ,
    MINUS_EQ,
    NULL;

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
            put(TokenTypeEnum.SUB, "SUB");
            put(TokenTypeEnum.MULTIPLY, "MULTIPLY");
            put(TokenTypeEnum.DIVIDE, "DIVIDE");
            put(TokenTypeEnum.IDENT, "IDENT");
            put(TokenTypeEnum.ASSIGN, "ASSIGN");
            put(TokenTypeEnum.LET, "LET");
            put(TokenTypeEnum.RETURN, "RETURN");
            put(TokenTypeEnum.FUNCTION, "FUNCTION");
            put(TokenTypeEnum.DEF, "DEF");
            put(TokenTypeEnum.IF, "IF");
            put(TokenTypeEnum.ELSE, "ELSE");
            put(TokenTypeEnum.LPAREN, "LPAREN");
            put(TokenTypeEnum.RPAREN, "RPAREN");
            put(TokenTypeEnum.LBRACE, "LBRACE");
            put(TokenTypeEnum.RBRACE, "RBRACE");
            put(TokenTypeEnum.TRUE, "TRUE");
            put(TokenTypeEnum.FALSE, "FALSE");
            put(TokenTypeEnum.WHILE, "WHILE");
            put(TokenTypeEnum.FOR, "FOR");
            put(TokenTypeEnum.BREAK, "BREAK");
            put(TokenTypeEnum.CONTINUE, "CONTINUE");
            put(TokenTypeEnum.SINGLECOMMENT, "SINGLE_COMMENT");
            put(TokenTypeEnum.MULTICOMMENT, "MULTI_COMMENT");
            put(TokenTypeEnum.SEMICOLON, "SEMICOLON");
            put(TokenTypeEnum.GT, "GT");
            put(TokenTypeEnum.LT, "LT");
            put(TokenTypeEnum.GTE, "GTE");
            put(TokenTypeEnum.LTE, "LTE");
            put(TokenTypeEnum.EQUALS, "EQUALS");
            put(TokenTypeEnum.NOT_EQUALS, "NOT_EQUALS");
            put(TokenTypeEnum.CLASS, "CLASS");
            put(TokenTypeEnum.THIS, "THIS");
            put(TokenTypeEnum.SUPER, "SUPER");
            put(TokenTypeEnum.PLUSPLUS, "PLUSPLUS");
            put(TokenTypeEnum.MINUSMINUS, "MINUSMINUS");
            put(TokenTypeEnum.PLUS_EQ, "PLUS_EQUAL");
            put(TokenTypeEnum.MINUS_EQ, "MINUS_EQUAL");
            put(TokenTypeEnum.NULL, "NULL");
        }
    };

    public static TokenTypeEnum convertToKeyword(String identifier) {
        return keywords.get(identifier);
    }

    public static String convertToString(TokenTypeEnum type) {
        return mapToString.get(type);
    }
}
