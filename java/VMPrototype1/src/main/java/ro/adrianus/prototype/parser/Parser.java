package ro.adrianus.prototype.parser;

import ro.adrianus.prototype.ast.AstNode;
import ro.adrianus.prototype.token.TokenTypeEnum;

import java.util.HashMap;
import java.util.function.Function;
import java.util.function.Supplier;

public class Parser {
    private HashMap<TokenTypeEnum, Supplier<AstNode>> prefixParseFns = new HashMap<>();
    private HashMap<TokenTypeEnum, Function<AstNode, AstNode>> infixParseFns = new HashMap<>();

    public Parser() {
        prefixParseFns.put(TokenTypeEnum.MINUS, this::parsePrefixExpression);
        infixParseFns.put(TokenTypeEnum.PLUS, this::parseInfixExpression);
        infixParseFns.put(TokenTypeEnum.MINUS, this::parseInfixExpression);
        infixParseFns.put(TokenTypeEnum.MULTIPLY, this::parseInfixExpression);
        infixParseFns.put(TokenTypeEnum.DIVIDE, this::parseInfixExpression);
    }

    AstNode parsePrefixExpression() {
        return null;
    }

    AstNode parseInfixExpression(AstNode left) {
        return null;
    }
}
