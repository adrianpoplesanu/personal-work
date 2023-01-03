package ast;

import token.Token;

public class ASTExpressionStatement extends AbstractASTNode {
    private ASTNode expression;

    public ASTExpressionStatement(Token token) {
        this.token = token;
        type = ASTNodeTypeEnum.EXPRESSION_STATEMENT;
    }

    @Override
    public ASTNodeTypeEnum getType() {
        return type;
    }

    @Override
    public String inspect() {
        return null;
    }

    public ASTNode getExpression() {
        return expression;
    }

    public void setExpression(ASTNode expression) {
        this.expression = expression;
    }
}
