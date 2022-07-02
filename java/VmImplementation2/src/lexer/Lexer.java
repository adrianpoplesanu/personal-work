package lexer;

import token.Token;
import token.TokenType;

import java.util.HashMap;
import java.util.Map;

public class Lexer {
    private String source;
    private int position;
    private int readPosition;
    private char currentChar;
    private Map<String, TokenType> keywordMap;

    public Lexer() {
        source = "";
        position = 0;
        readPosition = 0;
        currentChar = 0;
        keywordMap = new HashMap<>();
        constructKeywordMap();
    }

    public void load(String source) {
        this.source = source;
        this.position = 0;
        this.readPosition = 0;
        this.currentChar = 0;
        readChar();
    }

    private void constructKeywordMap() {
        keywordMap.put("let", TokenType.LET);
    }

    private void readChar() {
        if (readPosition >= source.length()) {
            currentChar = 0;
        } else {
            currentChar = source.charAt(readPosition);
        }
        position = readPosition;
        readPosition++;
    }

    private void skipWhitespaces() {
        while (currentChar == ' ' || currentChar == '\r' || currentChar == '\t' || currentChar == '\n') readChar();
    }

    private void peekChar() {

    }

    private String readIdentifier() {
        int start = position;
        while(isLetter()) {
            readChar();
        }
        return source.substring(start, position);
    }

    private String readNumber() {
        int start = position;
        while (isDigit()) {
            readChar();
        }
        return source.substring(start, position);
    }

    private boolean isDigit() {
        return currentChar >= '0' && currentChar <= '9';
    }

    private boolean isLetter() {
        return (currentChar >= 'a' && currentChar <= 'z') || (currentChar >= 'A' && currentChar <= 'Z') || currentChar == '_';
    }

    private TokenType lookupKeyword(String literal) {
        if (keywordMap.containsKey(literal)) return keywordMap.get(literal);
        return TokenType.IDENT;
    }

    public Token nextToken() {
        Token token = new Token();
        skipWhitespaces();
        boolean needsNextChar = true;
        switch (currentChar) {
            case 0:
                token.setLiteral("");
                token.setType(TokenType.EOF);
                break;
            case '+':
                token.setLiteral("+");
                token.setType(TokenType.PLUS);
                break;
            case '=':
                token.setLiteral("=");
                token.setType(TokenType.ASSIGN);
                break;
            default:
                if (isDigit()) {
                    needsNextChar = false;
                    token.setLiteral(readNumber());
                    token.setType(TokenType.INT);
                }
                else if (isLetter()) {
                    needsNextChar = false;
                    token.setLiteral(readIdentifier());
                    token.setType(lookupKeyword(token.getLiteral()));
                } else {
                    token.setLiteral("");
                    token.setType(TokenType.ILLEGAL);
                }
        }
        if (needsNextChar) readChar();
        return token;
    }
}
