package parser;

import ast.ASTNode;
import ast.ASTProgram;
import lexer.Lexer;
import token.Token;
import token.TokenTypeEnum;

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

    private void nextToken() {
        currentToken = peekToken;
        peekToken = lexer.nextToken();
    }

    public void parseProgram(ASTNode node) {
        ASTProgram program = (ASTProgram) node;
        while(currentToken.getType() != TokenTypeEnum.EOF) {
            System.out.println(currentToken);
            nextToken();
        }
    }
}
