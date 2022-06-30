package lexer;

import token.Token;

public class Lexer {
    private String source;
    private int position;
    private int readPosition;
    private char currentChar;

    public Lexer() {
        source = "";
        position = 0;
        readPosition = 0;
        currentChar = 0;
    }

    public void load(String source) {
        this.source = source;
        this.position = 0;
        this.readPosition = 0;
        this.currentChar = 0;
    }

    private void readChar() {
        if (readPosition >= source.length()) {
            currentChar = 0;
        } else {
            currentChar = source.charAt(readPosition);
            position = readPosition;
            readPosition++;
        }
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

    public Token nextToken() {
        Token token = new Token();
        skipWhitespaces();
        switch (currentChar) {
            case '+':
                break;
            default:
                if (isDigit()) {
                    //...
                }
                if (isLetter()) {
                    //...
                }
        }
        return token;
    }
}
