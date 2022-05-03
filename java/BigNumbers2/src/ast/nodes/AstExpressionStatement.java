package ast.nodes;

import ast.AstNode;
import ast.AstNodeType;

public class AstExpressionStatement extends AstNode {

    private AstNode expression;

    public AstExpressionStatement() {
        type = AstNodeType.EXPRESSION_STATEMENT;
    }

    public AstExpressionStatement(AstNode expression) {
        this();
        this.expression = expression;
    }

    @Override
    public String tokenLiteral() {
        return null;
    }

    @Override
    public String toString() {
        return "AstNode [AstExpressionStatement]";
    }

    public AstNode getExpression() {
        return expression;
    }

    public void setExpression(AstNode expression) {
        this.expression = expression;
    }
}
