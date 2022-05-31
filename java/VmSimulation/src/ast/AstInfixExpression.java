package ast;

import token.Token;

public class AstInfixExpression {
    private Token token;
    private String operator;
    private AstNode left;
    private AstNode right;
}
