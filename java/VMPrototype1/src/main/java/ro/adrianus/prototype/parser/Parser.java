package ro.adrianus.prototype.parser;

import ro.adrianus.prototype.ast.AstNode;
import ro.adrianus.prototype.ast.AstProgram;
import ro.adrianus.prototype.lexer.Lexer;
import ro.adrianus.prototype.token.Token;
import ro.adrianus.prototype.token.TokenTypeEnum;

import java.util.HashMap;
import java.util.function.Function;
import java.util.function.Supplier;

public class Parser {
    private Lexer lexer;
    private String source;
    private Token currentToken;
    private Token peekToken;
    private HashMap<TokenTypeEnum, Supplier<AstNode>> prefixParseFns = new HashMap<>();
    private HashMap<TokenTypeEnum, Function<AstNode, AstNode>> infixParseFns = new HashMap<>();

    public Parser() {
        lexer = new Lexer();
        prefixParseFns.put(TokenTypeEnum.SUB, this::parsePrefixExpression);
        infixParseFns.put(TokenTypeEnum.PLUS, this::parseInfixExpression);
        infixParseFns.put(TokenTypeEnum.SUB, this::parseInfixExpression);
        infixParseFns.put(TokenTypeEnum.MULTIPLY, this::parseInfixExpression);
        infixParseFns.put(TokenTypeEnum.DIVIDE, this::parseInfixExpression);
    }

    public void load(String s) {
        source = s;
        lexer.load(source);
        nextToken();
        nextToken();
    }

    public void buildProgramStatements(AstProgram program) {
        while(currentToken.getType() != TokenTypeEnum.EOF) {

        }
    }

    public void nextToken() {
        currentToken = peekToken;
        currentToken = lexer.nextToken();
    }

    AstNode parsePrefixExpression() {
        return null;
    }

    AstNode parseInfixExpression(AstNode left) {
        return null;
    }
}
