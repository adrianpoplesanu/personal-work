package com.adrianpoplesanu.lexer;

import com.adrianpoplesanu.token.Token;

public class Lexer {
    private String source;
    private char currentChar;
    private int position;
    private int readPosition;

    public Lexer(String source) {
        load(source);
    }

    public void load(String source) {
        this.source = source;
        currentChar = 0;
        position = 0;
        readPosition = 0;
        readChar();
    }

    public Token nextToken() {
        return null;
    }

    private void readChar() {
        // ...
    }
}
