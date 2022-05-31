package parser;

import ast.AstExpressionStatement;
import ast.AstNode;
import ast.AstProgram;
import lexer.Lexer;
import token.Token;
import token.TokenType;

public class Parser {
    private Token currentToken;
    private Token peekToken;
    private Lexer lexer;
    private String source;

    public Parser () {
        lexer = new Lexer();
    }

    public void buildProgramStatements(AstProgram program) {
        while (currentToken.getType() != TokenType.EOF) {
            System.out.println(currentToken);
            AstNode node = parseStatement();
            if (node != null) {
                program.statements.add(node);
            }
            nextToken();
        }
    }

    private AstNode parseStatement() {
        return parseExpressionStatement();
    }

    private AstNode parseExpressionStatement() {
        AstExpressionStatement stmt = new AstExpressionStatement(currentToken);
        stmt.setExpression(parseExpression(PrecedenceTypeEnum.LOWEST));
        if (peekTokenIs(TokenType.SEMICOLON)) {
            nextToken();
        }
        return stmt;
    }

    private AstNode parseExpression(PrecedenceTypeEnum precedenceTypeEnum) {
        return null;
    }

    private boolean peekTokenIs(TokenType tokenType) {
        return peekToken.type == tokenType;
    }

    private void nextToken() {
        currentToken = peekToken;
        peekToken = lexer.nextToken();
    }

    public void load(String source) {
        this.source = source;
        lexer.load(source);
        nextToken();
        nextToken();
    }
}
