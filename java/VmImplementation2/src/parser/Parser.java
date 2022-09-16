package parser;

import ast.AstNode;
import ast.nodes.*;
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
    private Map<TokenType, PrecedenceType> precedenceMap = new HashMap<>();

    public Parser() {
        lexer = new Lexer();
        prefixParseFns.put(TokenType.IDENT, this::parseIdentifier);
        prefixParseFns.put(TokenType.MINUS, this::parsePrefixExpression);
        prefixParseFns.put(TokenType.INT, this::parseIntegerLiteral);
        infixParseFns.put(TokenType.PLUS, this::parseInfixExpression);
        infixParseFns.put(TokenType.ASSIGN, this::parseAssignExpression);
        constructPrecedences();
    }

    private void constructPrecedences() {
        precedenceMap.put(TokenType.PLUS, PrecedenceType.SUM);
        precedenceMap.put(TokenType.MINUS, PrecedenceType.SUM);
        precedenceMap.put(TokenType.MULTIPLY, PrecedenceType.MULTIPLY);
        precedenceMap.put(TokenType.DIVIDE, PrecedenceType.MULTIPLY);
        precedenceMap.put(TokenType.ASSIGN, PrecedenceType.ASSIGN);
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
            AstNode statement = parseStatement();
            if (statement != null) {
                //System.out.println(statement);
                program.getStatements().add(statement);
            }
            nextToken();
        }
    }

    private AstNode parseStatement() {
        // if let statement return parseLetStatement
        // if return statement return parseReturnStatement
        return parseExpressionStatement();
    }

    private AstNode parseExpressionStatement() {
        AstExpressionStatement stmt = new AstExpressionStatement(currentToken);
        stmt.setExpression(parseExpression(PrecedenceType.LOWEST));
        if (peekTokenIs(TokenType.SEMICOLON)) {
            nextToken();
        }
        return stmt;
    }

    private AstNode parseExpression(PrecedenceType precedence) {
        if (!prefixParseFns.containsKey(currentToken.getType())) {
            return null;
        }
        Supplier<AstNode> prefix = prefixParseFns.get(currentToken.getType());
        AstNode leftExpression = prefix.get();
        while (!peekTokenIs(TokenType.SEMICOLON) && precedence.ordinal() < peekPrecedence().ordinal()) {
            if (!infixParseFns.containsKey(peekToken.getType())) return leftExpression;
            Function<AstNode, AstNode> infix = infixParseFns.get(peekToken.getType());
            nextToken();
            leftExpression = infix.apply(leftExpression);
        }
        return leftExpression;
    }

    private boolean currentTokenIs(TokenType type) {
        return currentToken.getType() == type;
    }

    private boolean peekTokenIs(TokenType type) {
        return peekToken.getType() == type;
    }

    private PrecedenceType currentPrecedence() {
        if (precedenceMap.containsKey(currentToken.getType())) return precedenceMap.get(currentToken.getType());
        return PrecedenceType.LOWEST;
    }

    private PrecedenceType peekPrecedence() {
        if (precedenceMap.containsKey(peekToken.getType())) return precedenceMap.get(peekToken.getType());
        return PrecedenceType.LOWEST;
    }

    private AstNode parseIdentifier() {
        AstIdent ident = new AstIdent(currentToken, currentToken.getLiteral());
        return ident;
    }

    private AstNode parsePrefixExpression() {
        AstPrefixExpression expr = new AstPrefixExpression(currentToken);
        nextToken();
        expr.setRight(parseExpression(PrecedenceType.PREFIX));
        return expr;
    }

    private AstNode parseInfixExpression(AstNode left) {
        AstInfixExpression expr = new AstInfixExpression(currentToken, currentToken.getLiteral(), left);
        PrecedenceType precedence = currentPrecedence();
        nextToken();
        expr.setRight(parseExpression(precedence));
        return expr;
    }

    private AstNode parseIntegerLiteral() {
        AstInteger node = new AstInteger(currentToken, Integer.valueOf(currentToken.getLiteral()));
        return node;
    }

    private AstNode parseAssignExpression(AstNode left) {
        AstAssignExpression stmt = new AstAssignExpression(currentToken);
        stmt.setName(left);
        nextToken();
        AstNode right = parseExpression(PrecedenceType.LOWEST);
        stmt.setValue(right);
        if (currentTokenIs(TokenType.SEMICOLON)) {
            nextToken();
        }
        return stmt;
    }
}
