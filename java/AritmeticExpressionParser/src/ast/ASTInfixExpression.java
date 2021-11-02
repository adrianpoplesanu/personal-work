package ast;

public class ASTInfixExpression extends ASTNode {
    private ASTNode left;
    private ASTNode right;
    private String operator;

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

    public String toString() {
        return "(" + left.toString() + operator + right.toString() + ")";
    }
}
