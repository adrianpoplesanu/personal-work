package ast;

import token.Token;

public class AstPrefixExpression {
    private Token token;
    private String operator;
    private AstNode right;
}
