package ast;

import token.Token;

public class AstInfixExpression extends AstNode {
    public Token token;
    public String operator;
    public AstNode left;
    public AstNode right;

    public String toString() {
        return "[AstInfixExpression] <" + left + " " + operator + " " + right + ">";
    }
}
