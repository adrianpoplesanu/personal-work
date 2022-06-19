package lexer;

public interface Lexer {
    void readChar();
    void skipWhitespaces();
    void peekChar();
    String readIdentifier();
    String readNumber();
}
