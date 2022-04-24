package lexer;

import token.Token;

public class Lexer {
    private String source;
    private char currentChar;
    private int position;
    private int readPosition;

    public Lexer() {
        position = 0;
        readPosition = 0;
    }

    public void load(String source) {
        this.source = source;
        position = 0;
        readPosition = 0;
    }

    private void skipWhitespaces() {
        while (currentChar == ' ') readChar();
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

    private char peekChar() {
        if (readPosition >= source.length()) return 0;
        return source.charAt(readPosition);
    }

    private String readBigNumber() {
        return null;
    }

    public Token nextToken() {
        skipWhitespaces();
        return null;
    }
}
