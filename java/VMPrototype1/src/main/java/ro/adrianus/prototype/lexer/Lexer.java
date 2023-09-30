package ro.adrianus.prototype.lexer;

import ro.adrianus.prototype.token.Token;
import ro.adrianus.prototype.token.TokenTypeEnum;

public class Lexer {
    private String source;
    private char currentChar;
    private int position;
    private int readPosition;
    public void load(String s) {
        source = s;
        currentChar = 0;
        position = 0;
        readPosition = 0;
        readChar();
    }

    public void skipWhitespaces() {
        while(currentChar == ' ' || currentChar == '\t' || currentChar == '\r' || currentChar == '\n') {
            readChar();
        }
    }

    public Token nextToken() {
        Token token = new Token(TokenTypeEnum.EOF, "");
        return token;
    }

    private void readChar() {

    }
}
