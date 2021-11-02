package lexer;

import token.Token;

import java.util.ArrayList;

public class Lexer {
    private String source;
    private int pos;
    private char currentChar;

    public void load(String source) {
        this.source = source;
        pos = 0;
        readChar();
    }

    private void readChar() {
        if (pos >= source.length()) {
            currentChar = 0;
        } else {
            currentChar = source.charAt(pos);
            pos++;
        }
    }

    private boolean isDigit() {
        return ('0' <= currentChar) && (currentChar <= '9');
    }

    public ArrayList<Token> getAllTokens() {
        ArrayList<Token> tokens = new ArrayList<>();
        while(currentChar != 0) {
            switch(currentChar) {
                case '+':
                    tokens.add(new Token("PLUS", "+"));
                    break;
                case '-':
                    tokens.add(new Token("MINUS", "-"));
                    break;
                case '*':
                    tokens.add(new Token("ASTERISK", "*"));
                    break;
                case '/':
                    tokens.add(new Token("SLASH", "/"));
                    break;
                case '(':
                    tokens.add(new Token("LPAREN", "("));
                    break;
                case ')':
                    tokens.add(new Token("RPAREN", ")"));
                    break;
                default:
                    if (isDigit()) {
                        int start = pos - 1;
                        while(isDigit()) {
                            readChar();
                        }
                        if (currentChar == 0) {
                            tokens.add(new Token("INT", source.substring(start, pos)));
                        } else {
                            tokens.add(new Token("INT", source.substring(start, pos - 1)));
                        }
                        continue;
                    }
                    break;
            }
            readChar();
        }
        tokens.add(new Token("EOF", "EOF"));
        return tokens;
    }
}
