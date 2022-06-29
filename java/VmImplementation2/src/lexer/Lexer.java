package lexer;

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

    public void readChar() {
        if (readPosition >= source.length()) {
            currentChar = 0;
        } else {
            currentChar = source.charAt(readPosition);
            position = readPosition;
            readPosition++;
        }
    }

    public void skipWhitespaces() {

    }

    public void peekChar() {

    }

    public String readIdentifier() {
        return null;
    }

    public String readNumber() {
        return null;
    }
}
