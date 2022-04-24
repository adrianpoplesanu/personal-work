package parser;

import lexer.Lexer;
import token.Token;

public class Parser {
    private Lexer lexer;
    private Token currentToken;
    private Token peekToken;

    private void buildProgramStatements() {

    }

    private void nextToken() {
        currentToken = peekToken;
        peekToken = lexer.nextToken();
    }
}
