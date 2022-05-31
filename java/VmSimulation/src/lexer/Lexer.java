package lexer;

import token.Token;
import token.TokenType;

public class Lexer {

    private String source;
    private char currentChar;
    private int position;
    private int readPosition;

    public Lexer () {
        source = "";
        currentChar = 0;
        position = 0;
        readPosition = 0;
    }

    public void load(String source) {
        this.source = source;
        currentChar = 0;
        position = 0;
        readPosition = 0;
        readChar();
    }

    private void skipWhitespaces() {
        while((currentChar == ' ') || (currentChar == '\t') || (currentChar == '\r') || (currentChar == '\n')) {
            readChar();
        }
    }

    private boolean isDigit() {
        return currentChar >= '0' && currentChar <= '9';
    }

    private String readNumber() {
        int start = position;
        while(isDigit()) {
            readChar();
        }
        return source.substring(start, position);
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

    public Token nextToken() {
        Token token = new Token();
        skipWhitespaces();
        switch (currentChar) {
            case 0:
                token.literal = "";
                token.type = TokenType.EOF;
                break;
            case '+':
                token.literal = "+";
                token.type = TokenType.PLUS;
                break;
            default:
                if (isDigit()) {
                    token.literal = readNumber();
                    token.type = TokenType.INT;
                    return token;
                }
                break;
        }
        readChar();
        return token;
    }
}
