package lexer;

import token.Token;
import token.TokenKeywordConverter;
import token.TokenType;

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
        readChar();
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
        int start = position;
        while(isDigit()) {
            readChar();
        }
        return source.substring(start, position);
    }

    private String readLiteral() {
        int start = position;
        while(isLetter()) {
            readChar();
        }
        while(isLetter() || isDigit()) {
            readChar();
        }
        return source.substring(start, position);
    }

    private boolean isDigit() {
        return '0' <= currentChar && currentChar <= '9';
    }

    private boolean isLetter() {
        return ('a' <= currentChar && currentChar <= 'z') || ('A' <= currentChar && currentChar <= 'Z') || currentChar == '_';
    }

    private boolean isFloatDot() {
        return currentChar == '.';
    }

    private String readIdentifier() {
        return null;
    }

    private TokenType lookupKeyword(String literal) {
        if (TokenKeywordConverter.checkKeyword(literal)) return TokenKeywordConverter.convertKeyword(literal);
        return TokenType.IDENT;
    }

    public Token nextToken() {
        skipWhitespaces();
        boolean readNextChar = true;
        Token result = new Token();

        switch (currentChar) {
            case 0:
                result.setTokenLiteral("");
                result.setType(TokenType.EOF);
                break;
            case '+':
                result.setTokenLiteral("+");
                result.setType(TokenType.SUM);
                break;
            case '-':
                result.setTokenLiteral("-");
                result.setType(TokenType.MINUS);
                break;
            case '*':
                result.setTokenLiteral("*");
                result.setType(TokenType.MULTIPLY);
                break;
            case '/':
                result.setTokenLiteral("/");
                result.setType(TokenType.DIVIDE);
                break;
            default:
                if (isLetter()) {
                    readNextChar = false;
                    String literal = readLiteral();
                    result.setTokenLiteral(literal);
                    result.setType(lookupKeyword(literal));
                } else if (isDigit()) {
                    readNextChar = false;
                    String literal = readBigNumber();
                    result.setTokenLiteral(literal);
                    result.setType(TokenType.BIG_NUMBER);
                } else {
                    result.setTokenLiteral(String.valueOf(currentChar));
                    result.setType(TokenType.UNDEFINED);
                }
                break;
        }

        if (readNextChar) {
            readChar();
        }
        return result;
    }
}
