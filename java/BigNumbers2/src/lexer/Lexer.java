package lexer;

import token.Token;

public class Lexer {
    private String source;
    private char currentChar;
    private int position;
    private int readPosition;

    public Lexer() {

    }

    public void load(String source) {
        this.source = source;
    }

    public Token nextToken() {
        return null;
    }
}
