package parser;

import ast.*;
import lexer.Lexer;
import parser.*;
import token.Token;

import java.util.ArrayList;
import java.util.HashMap;

public class Parser {
    private String source;
    private Lexer lexer;
    private ArrayList<Token> tokens;
    private int pos;
    private Token currentToken;
    private Token peekToken;
    private HashMap<String, PrefixParser> prefixFns;
    private HashMap<String, InfixParser> infixFns;

    public Parser() {
        lexer = new Lexer();
        prefixFns = new HashMap<>();
        infixFns = new HashMap<>();
        prefixFns.put("INT", new PrefixParserInteger(this));
        prefixFns.put("MINUS", new PrefixParserPrefixExpression(this));
        prefixFns.put("LPAREN", new PrefixParserGroupedExpression(this));
        infixFns.put("PLUS", new InfixParserExpression(this));
        infixFns.put("MINUS", new InfixParserExpression(this));
        infixFns.put("ASTERISK", new InfixParserExpression(this));
        infixFns.put("SLASH", new InfixParserExpression(this));
    }

    public void load(String source) {
        this.source = source;
        lexer.load(source);
        tokens = lexer.getAllTokens();
        pos = 0;
        currentToken = tokens.get(pos);
        peekToken = tokens.get(pos + 1);
    }

    public void nextToken() {
        pos++;
        if (pos < tokens.size()) currentToken = tokens.get(pos);
        else currentToken = null;
        if (pos + 1 < tokens.size()) peekToken = tokens.get(pos + 1);
        else peekToken = null;
    }

    private PrecedenceTypeEnum currentPrecedence() {
        switch(currentToken.getType()) {
            case "PLUS":
            case "MINUS":
                return PrecedenceTypeEnum.SUM;
            case "ASTERISK":
            case "SLASH":
                return PrecedenceTypeEnum.PRODUCT;
            case "LPAREN":
                return PrecedenceTypeEnum.CALL;
            default:
                return PrecedenceTypeEnum.LOWEST;
        }
    }

    private PrecedenceTypeEnum peekPrecedence() {
        switch(peekToken.getType()) {
            case "PLUS":
            case "MINUS":
                return PrecedenceTypeEnum.SUM;
            case "ASTERISK":
            case "SLASH":
                return PrecedenceTypeEnum.PRODUCT;
            case "LPAREN":
                return PrecedenceTypeEnum.CALL;
            default:
                return PrecedenceTypeEnum.LOWEST;
        }
    }

    public ASTNode parseInteger() {
        return new ASTInteger(currentToken.getVal());
    }

    public ASTNode parsePrefixExpression() {
        ASTPrefixExpression stmt = new ASTPrefixExpression();
        nextToken();
        stmt.setRight(parseExpression(PrecedenceTypeEnum.PREFIX));
        return stmt;
    }

    public ASTNode parseGroupedExpression() {
        nextToken();
        ASTNode expr = parseExpression(PrecedenceTypeEnum.LOWEST);
        if (peekToken.getType() == "RPAREN") nextToken();
        return expr;
    }

    public ASTNode parseInfixExpression(ASTNode left) {
        ASTInfixExpression expr = new ASTInfixExpression();
        expr.setLeft(left);
        expr.setOperator(currentToken.getVal());
        PrecedenceTypeEnum precedence = currentPrecedence();
        nextToken();
        expr.setRight(parseExpression(precedence));
        return expr;
    }

    private ASTNode parseExpression(PrecedenceTypeEnum precedence) {
        if (!prefixFns.containsKey(currentToken.getType())) return null;
        PrefixParser prefix = prefixFns.get(currentToken.getType());
        ASTNode left = prefix.call();
        while (precedence.ordinal() < peekPrecedence().ordinal()) {
            if (!infixFns.containsKey(peekToken.getType())) return left;
            InfixParser infix = infixFns.get(peekToken.getType());
            nextToken();
            left = infix.call(left);
        }
        return left;
    }

    private ASTNode parseExpressionStatement() {
        ASTExpressionStatement stmt = new ASTExpressionStatement();
        stmt.setExpression(parseExpression(PrecedenceTypeEnum.LOWEST));
        return stmt;
    }

    public void buildStatements() {
        while(currentToken.getType() != "EOF") {
            ASTNode stmt = parseExpressionStatement();
            nextToken();
            System.out.println(stmt);
        }
    }
}
