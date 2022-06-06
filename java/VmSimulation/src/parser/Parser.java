package parser;

import ast.*;
import lexer.Lexer;
import token.Token;
import token.TokenType;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;
import java.util.function.Supplier;

public class Parser {
    private Token currentToken;
    private Token peekToken;
    private Lexer lexer;
    private String source;

    private Map<TokenType, Supplier<AstNode>> prefixParseFunctions = new HashMap<>();
    private Map<TokenType, Function<AstNode, AstNode>> infixParseFunctions = new HashMap<>();

    private Map<TokenType, PrecedenceTypeEnum> precedences = new HashMap<>();

    public Parser () {
        lexer = new Lexer();
        prefixParseFunctions.put(TokenType.INT, this::parseIntegerLiteral);
        infixParseFunctions.put(TokenType.PLUS, this::parseInfixExpression);
        infixParseFunctions.put(TokenType.MINUS, this::parseInfixExpression);
        infixParseFunctions.put(TokenType.DIVIDE, this::parseInfixExpression);
        infixParseFunctions.put(TokenType.MULTIPLY, this::parseInfixExpression);

        precedences.put(TokenType.PLUS, PrecedenceTypeEnum.SUM);
        precedences.put(TokenType.MINUS, PrecedenceTypeEnum.SUM);
        precedences.put(TokenType.DIVIDE, PrecedenceTypeEnum.PRODUCT);
        precedences.put(TokenType.MULTIPLY, PrecedenceTypeEnum.PRODUCT);
    }

    public void buildProgramStatements(AstProgram program) {
        while (currentToken.getType() != TokenType.EOF) {
            //System.out.println(currentToken);
            AstNode node = parseStatement();
            //System.out.println(node);
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

    private AstNode parseExpression(PrecedenceTypeEnum pte) {
        if (!prefixParseFunctions.containsKey(currentToken.getType())) {
            return null;
        }
        Supplier<AstNode> prefix = prefixParseFunctions.get(currentToken.getType());
        AstNode leftExpression = prefix.get();
        while (!peekTokenIs(TokenType.SEMICOLON) && pte.ordinal() < peekPrecedence().ordinal()) {
            if (!infixParseFunctions.containsKey(peekToken.getType())) return leftExpression;
            Function<AstNode, AstNode> infix = infixParseFunctions.get(peekToken.getType());
            nextToken();
            leftExpression = infix.apply(leftExpression);
        }
        return leftExpression;
    }

    private AstNode parseInfixExpression(AstNode left) {
        AstInfixExpression expr = new AstInfixExpression();
        expr.token = getCurrentToken();
        expr.operator = getCurrentToken().literal;
        expr.left = left;
        PrecedenceTypeEnum precedence = currentPrecedence();
        nextToken();
        expr.right = parseExpression(precedence);
        return expr;
    }

    private AstNode parseIntegerLiteral() {
        String value = getCurrentToken().literal;
        return new AstInteger(getCurrentToken(), Integer.parseInt(value));
    }

    private PrecedenceTypeEnum currentPrecedence() {
        return precedences.get(currentToken.type);
    }

    private PrecedenceTypeEnum peekPrecedence() {
        if (precedences.containsKey(peekToken.type)) return precedences.get(peekToken.type);
        return PrecedenceTypeEnum.LOWEST;
    }

    private Token getCurrentToken() {
        return currentToken;
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
