package parser;

import ast.AstNode;
import ast.nodes.AstBoolean;
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
}
