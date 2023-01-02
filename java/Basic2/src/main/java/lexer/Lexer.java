package lexer;

public class Lexer {
    private String source;

    public Lexer() {
        this.source = "";
    }

    public void load(String source) {
        this.source = source;
    }
}
