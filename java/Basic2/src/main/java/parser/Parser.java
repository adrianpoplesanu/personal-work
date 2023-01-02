package parser;

import lexer.Lexer;

public class Parser {
    private Lexer lexer;
    public Parser() {
        lexer = new Lexer();
    }

    public void load(String source) {
        lexer.load(source);
    }
}
