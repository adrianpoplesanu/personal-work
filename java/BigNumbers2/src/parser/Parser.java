package parser;

import ast.AstNode;
import ast.nodes.AstBoolean;
import ast.nodes.AstIdentifier;
import ast.nodes.AstLetStatement;
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
    private Map<TokenType, Supplier<AstNode>> prefixParseFunctions;
    private Map<TokenType, Function<AstNode, AstNode>> infixParseFunctions;

    public Parser() {
        lexer = new Lexer();
        prefixParseFunctions = new HashMap<>();
        infixParseFunctions = new HashMap<>();

        prefixParseFunctions.put(TokenType.BIG_NUMBER, this::parseBigNumber);
        prefixParseFunctions.put(TokenType.TRUE, this::parseTrueLiteral);
        prefixParseFunctions.put(TokenType.FALSE, this::parseFalseLiteral);
        prefixParseFunctions.put(TokenType.IF, this::parseIfStatement);
        prefixParseFunctions.put(TokenType.LPAREN, this::parseGroupExpression);
        infixParseFunctions.put(TokenType.SUM, this::parseInfixExpression);
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

    private boolean currentTokenIs(TokenType tokenType) {
        return currentToken.getType() == tokenType;
    }

    private boolean peekTokenIs(TokenType tokenType) {
        return peekToken.getType() == tokenType;
    }

    private boolean expectPeek(TokenType tokenType) {
        if (peekTokenIs(tokenType)) {
            nextToken();
            return true;
        }
        return false;
    }

    public void buildProgramStatements(AstProgram program) {
        while(currentToken.getType() != TokenType.EOF) {
            System.out.println(currentToken);
            AstNode result = parseStatement();
            if (result != null) program.getStatements().add(result);
            nextToken();
        }
    }

    private AstNode parseStatement() {
        if (currentToken.getType() == TokenType.LET) {
            return parseLetStatement();
        }
        return parseExpressionStatement();
    }

    private AstNode parseLetStatement() {
        AstLetStatement stmt = new AstLetStatement();
        if (!expectPeek(TokenType.IDENT)) {
            return null;
        }
        stmt.setName(new AstIdentifier(currentToken));
        if (!expectPeek(TokenType.ASSIGN)) {
            return null;
        }
        nextToken();
        AstNode expr = parseExpression(PrecedenceType.LOWEST);
        stmt.setValue(expr);
        if (currentTokenIs(TokenType.SEMICOLON)) {
            nextToken();
        }
        return stmt;
    }

    private AstNode parseExpressionStatement() {
        return null;
    }

    private AstNode parseExpression(PrecedenceType precedence) {
        return null;
    }

    private AstNode parseBigNumber() {
        return null;
    }

    private AstNode parseTrueLiteral() {
        return new AstBoolean(true);
    }

    private AstNode parseFalseLiteral() {
        return new AstBoolean(false);
    }

    private AstNode parseIfStatement() {
        return null;
    }

    private AstNode parseGroupExpression() {
        return null;
    }

    private AstNode parsePrefixExpression() {
        return null;
    }

    private AstNode parseInfixExpression(AstNode left) {
        return null;
    }
}
