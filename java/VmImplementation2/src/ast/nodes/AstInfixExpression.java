package ast.nodes;

import ast.AbstractAstNode;
import ast.AstNodeType;
import token.Token;

public class AstInfixExpression extends AbstractAstNode {

    public AstInfixExpression() {
        type = AstNodeType.INFIX_EXPRESSION;
    }

    public AstInfixExpression(Token token) {
        this();
        setToken(token);
    }

    @Override
    public String inspect() {
        return null;
    }
}
