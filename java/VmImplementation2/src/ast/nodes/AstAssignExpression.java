package ast.nodes;

import ast.AbstractAstNode;
import ast.AstNode;
import ast.AstNodeType;
import token.Token;

public class AstAssignExpression extends AbstractAstNode {
    private AstNode name;
    private AstNode value;

    public AstAssignExpression(Token token) {
        type = AstNodeType.ASSIGN_EXPRESSION;
        this.token = token;
    }

    @Override
    public String toString() {
        return "AstAssignExpression [] <><>";
    }

    public AstNode getName() {
        return name;
    }

    public void setName(AstNode name) {
        this.name = name;
    }

    public AstNode getValue() {
        return value;
    }

    public void setValue(AstNode value) {
        this.value = value;
    }
}
