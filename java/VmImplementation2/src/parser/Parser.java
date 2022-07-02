package parser;

import ast.AstNode;
import ast.nodes.AstProgram;
import lexer.Lexer;
import token.Token;
import token.TokenType;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;
import java.util.function.Supplier;

public class Parser {
    private Lexer lexer;
    private Token currentToken;
    private Token peekToken;
    private String source;
    private Map<TokenType, Supplier<AstNode>> prefixParseFns = new HashMap<>();
    private Map<TokenType, Function<AstNode, AstNode>> infixParseFns = new HashMap<>();

    public Parser() {
        lexer = new Lexer();
        prefixParseFns.put(TokenType.IDENT, this::parseIdentifier);
        prefixParseFns.put(TokenType.MINUS, this::parsePrefixExpression);
        infixParseFns.put(TokenType.PLUS, this::parseInfixExpression);
    }

    public void load(String source) {
        this.source = source;
        lexer.load(source);
        nextToken();
        nextToken();
    }

    private void nextToken() {
        currentToken = peekToken;
        peekToken = lexer.nextToken();
    }

    public void buildStatements(AstProgram program) {
        while (currentToken.getType() != TokenType.EOF) {
            System.out.println(currentToken);
            AstNode statement = parseStatement();
            if (statement != null) {
                program.getStatements().add(statement);
            }
            nextToken();
        }
    }

    private AstNode parseStatement() {
        return null;
    }

    private AstNode parseIdentifier() {
        return null;
    }

    private AstNode parsePrefixExpression() {
        return null;
    }

    private AstNode parseInfixExpression(AstNode left) {
        return null;
    }
}
