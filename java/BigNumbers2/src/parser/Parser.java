package parser;

import lexer.Lexer;
import token.Token;
import token.TokenType;

public class Parser {
    private Lexer lexer;
    private Token currentToken;
    private Token peekToken;

    public Parser() {
        lexer = new Lexer();
    }

    public void load(String source) {
        lexer.load(source);
        nextToken();
        nextToken();
    }

    public void buildProgramStatements() {
        while(currentToken.getType() != TokenType.EOF) {
            System.out.println(currentToken);
            nextToken();
        }
    }

    private void nextToken() {
        currentToken = peekToken;
        peekToken = lexer.nextToken();
    }
}
