package ast;

public class ASTExpressionStatement extends ASTNode {
    private ASTNode expression;

    public ASTNode getExpression() {
        return expression;
    }

    public void setExpression(ASTNode expression) {
        this.expression = expression;
    }

    public String toString() {
        return expression.toString();
    }
}
