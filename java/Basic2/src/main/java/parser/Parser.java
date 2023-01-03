package parser;

import ast.*;
import lexer.Lexer;
import token.Token;
import token.TokenTypeEnum;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;
import java.util.function.Supplier;

public class Parser {
    private Lexer lexer;
    private Token currentToken;
    private Token peekToken;
    private Map<TokenTypeEnum, Supplier<ASTNode>> prefixParseFns = new HashMap<>();
    private Map<TokenTypeEnum, Function<ASTNode, ASTNode>> infixParseFns = new HashMap<>();

    public Parser() {
        lexer = new Lexer();
        prefixParseFns.put(TokenTypeEnum.INT, this::parseIntegerExpression);
        prefixParseFns.put(TokenTypeEnum.LPAREN, this::parseGroupedExpression);
        infixParseFns.put(TokenTypeEnum.PLUS, this::parseInfixExpression);
        infixParseFns.put(TokenTypeEnum.MINUS, this::parseInfixExpression);
        infixParseFns.put(TokenTypeEnum.MULTIPLY, this::parseInfixExpression);
        infixParseFns.put(TokenTypeEnum.DIVIDE, this::parseInfixExpression);
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

    private Token getCurrentToken() {
        return currentToken;
    }

    private Token getPeekToken() {
        return peekToken;
    }

    private boolean currentTokenIs(TokenTypeEnum tte) {
        return currentToken.getType() == tte;
    }

    private boolean peekTokenIs(TokenTypeEnum tte) {
        return peekToken.getType() == tte;
    }

    private boolean expectPeekToken(TokenTypeEnum tte) {
        if (peekTokenIs(tte)) {
            nextToken();
            return true;
        }
        return false;
    }

    private PrecedenceTypeEnum currentPrecedence() {
        if (PrecedenceConverter.hasPrecedenceBind(currentToken.getType())) {
            return PrecedenceConverter.convertTokenTypeToPrecedence(currentToken.getType());
        }
        return PrecedenceTypeEnum.LOWEST;
    }

    private PrecedenceTypeEnum peekPrecedence() {
        if (PrecedenceConverter.hasPrecedenceBind(peekToken.getType())) {
            return PrecedenceConverter.convertTokenTypeToPrecedence(peekToken.getType());
        }
        return PrecedenceTypeEnum.LOWEST;
    }

    public void parseProgram(ASTNode node) {
        ASTProgram program = (ASTProgram) node;
        while(currentToken.getType() != TokenTypeEnum.EOF) {
            ASTNode stmt = parseStatement();
            program.getStatements().add(stmt);
            nextToken();
        }
    }

    private ASTNode parseStatement() {
        // check if current token is a let, return, comment, etc type, if not return an expression statement
        return parseExpressionStatement();
    }

    private ASTNode parseExpressionStatement() {
        ASTExpressionStatement stmt = new ASTExpressionStatement(currentToken);
        stmt.setExpression(parseExpression(PrecedenceTypeEnum.LOWEST));
        return stmt;
    }

    private ASTNode parseIntegerExpression() {
        ASTInteger stmt = new ASTInteger(currentToken);
        stmt.setValue(Integer.valueOf(currentToken.getTokenLiteral()));
        return stmt;
    }

    private ASTNode parseGroupedExpression() {
        nextToken();
        ASTNode expr = parseExpression(PrecedenceTypeEnum.LOWEST);
        if (!expectPeekToken(TokenTypeEnum.RPAREN)) {
            return null;
        }
        return expr;
    }

    private ASTNode parseInfixExpression(ASTNode left) {
        ASTInfixExpression expr = new ASTInfixExpression(currentToken);
        expr.setOperator(currentToken.getTokenLiteral());
        expr.setLeft(left);
        PrecedenceTypeEnum currentPrecedence = currentPrecedence();
        nextToken();
        expr.setRight(parseExpression(currentPrecedence));
        return expr;
    }

    private ASTNode parseExpression(PrecedenceTypeEnum precedence) {
        if (!prefixParseFns.containsKey(currentToken.getType())) {
            return null;
        }

        Supplier<ASTNode> prefix = prefixParseFns.get(currentToken.getType());
        ASTNode leftExpr = prefix.get();

        while(!peekTokenIs(TokenTypeEnum.SEMICOLON) && (precedence.ordinal() < peekPrecedence().ordinal())) {
            if (!infixParseFns.containsKey(peekToken.getType())) {
                return leftExpr;
            }
            Function<ASTNode, ASTNode> infix = infixParseFns.get(peekToken.getType());
            nextToken();
            leftExpr = infix.apply(leftExpr);
        }

        return leftExpr;
    }
}
