package lexer;

import token.Token;
import token.TokenTypeEnum;

public class Lexer {
    private String source;
    private int position;
    private int readPosition;
    private char currentChar;

    public Lexer() {
        this.source = "";
    }

    public void load(String source) {
        this.source = source;
        position = 0;
        readPosition = 0;
        readChar();
    }

    private void readChar() {
        if (readPosition < source.length()) {
            currentChar = source.charAt(readPosition);
        } else {
            currentChar = 0;
        }
        position = readPosition;
        readPosition++;
    }

    private void skipWhitespaces() {
        while (currentChar == ' ' || currentChar == '\t' || currentChar == '\r' || currentChar == '\n') {
            readChar();
        }
    }

    private boolean isDigit() {
        return currentChar >= '0' && currentChar <= '9';
    }

    public Token nextToken() {
        Token token = new Token();
        skipWhitespaces();
        boolean flagReadNextChar = true;
        switch(currentChar) {
            case 0:
                token.setType(TokenTypeEnum.EOF);
                token.setTokenLiteral("");
                break;
            case '+':
                token.setType(TokenTypeEnum.PLUS);
                token.setTokenLiteral("+");
                break;
            case '-':
                token.setType(TokenTypeEnum.MINUS);
                token.setTokenLiteral("-");
                break;
            case '*':
                token.setType(TokenTypeEnum.MULTIPLY);
                token.setTokenLiteral("*");
                break;
            case '/':
                token.setType(TokenTypeEnum.DIVIDE);
                token.setTokenLiteral("/");
                break;
            default:
                if (isDigit()) {
                    int start = position;
                    while (isDigit()) {
                        readChar();
                    }
                    token.setType(TokenTypeEnum.INT);
                    token.setTokenLiteral(source.substring(start, position));
                    flagReadNextChar = false;
                }
                break;
        }
        if (flagReadNextChar) {
            readChar();
        }
        return token;
    }
}
