package ast.nodes;

import ast.AbstractAstNode;
import ast.AstNode;
import ast.AstNodeType;
import token.Token;

public class AstExpressionStatement extends AbstractAstNode {
    private AstNode expression;

    public AstExpressionStatement() {
        type = AstNodeType.EXPRESSION_STATEMENT;
    }

    public AstExpressionStatement(Token token) {
        this();
        setToken(token);
    }

    @Override
    public String toString() {
        return "AstExpressionStatement [" + token + "] < " + expression + " >";
    }

    public AstNode getExpression() {
        return expression;
    }

    public void setExpression(AstNode expression) {
        this.expression = expression;
    }
}
