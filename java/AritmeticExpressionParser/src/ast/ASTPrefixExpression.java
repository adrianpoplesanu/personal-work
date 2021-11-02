package ast;

public class ASTPrefixExpression extends ASTNode {
    private ASTNode right;

    public ASTNode getRight() {
        return right;
    }

    public void setRight(ASTNode right) {
        this.right = right;
    }

    public String toString() {
        return "-" + right.toString();
    }
}
