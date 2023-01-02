package parser;

import ast.ASTNode;
import ast.ASTProgram;
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
        return false;
    }

    private boolean peekTokenIs(TokenTypeEnum tte) {
        return false;
    }

    private boolean expectPeekToken(TokenTypeEnum tte) {
        if (peekTokenIs(tte)) {
            nextToken();
            return true;
        }
        return false;
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
        return null;
    }

    private ASTNode parseIntegerExpression() {
        return null;
    }

    private ASTNode parseInfixExpression(ASTNode left) {
        return null;
    }

    private ASTNode parseGroupedExpression() {
        return null;
    }

    private ASTNode parseExpression(PrecedenceTypeEnum precedence) {
        return null;
    }
}
