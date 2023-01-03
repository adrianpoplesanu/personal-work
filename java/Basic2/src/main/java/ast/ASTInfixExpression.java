package ast;

import token.Token;

public class ASTInfixExpression extends AbstractASTNode {
    private ASTNode left;
    private ASTNode right;
    private String operator;

    public ASTInfixExpression(Token token) {
        this.token = token;
        type = ASTNodeTypeEnum.INFIX_EXPRESSION;
    }

    @Override
    public ASTNodeTypeEnum getType() {
        return type;
    }

    @Override
    public String inspect() {
        return null;
    }

    public ASTNode getLeft() {
        return left;
    }

    public void setLeft(ASTNode left) {
        this.left = left;
    }

    public ASTNode getRight() {
        return right;
    }

    public void setRight(ASTNode right) {
        this.right = right;
    }

    public String getOperator() {
        return operator;
    }

    public void setOperator(String operator) {
        this.operator = operator;
    }
}
