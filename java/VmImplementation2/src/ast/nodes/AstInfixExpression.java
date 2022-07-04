package ast.nodes;

import ast.AbstractAstNode;
import ast.AstNode;
import ast.AstNodeType;
import token.Token;

public class AstInfixExpression extends AbstractAstNode {
    private String operator;
    private AstNode left;
    private AstNode right;

    public AstInfixExpression() {
        type = AstNodeType.INFIX_EXPRESSION;
    }

    public AstInfixExpression(Token token) {
        this();
        setToken(token);
    }

    public AstInfixExpression(Token token, String operator, AstNode left) {
        this(token);
        this.operator = operator;
        this.left = left;
    }

    @Override
    public String toString() {
        return "AstInfixExpression [" + token + "] <" + left + "> <" + operator + "> <" + right + ">";
    }

    public String getOperator() {
        return operator;
    }

    public void setOperator(String operator) {
        this.operator = operator;
    }

    public AstNode getLeft() {
        return left;
    }

    public void setLeft(AstNode left) {
        this.left = left;
    }

    public AstNode getRight() {
        return right;
    }

    public void setRight(AstNode right) {
        this.right = right;
    }
}
