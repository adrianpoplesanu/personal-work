package ast.nodes;

import ast.AbstractAstNode;
import ast.AstNodeType;
import token.Token;

public class AstExpressionStatement extends AbstractAstNode {

    public AstExpressionStatement() {
        type = AstNodeType.EXPRESSION_STATEMENT;
    }

    public AstExpressionStatement(Token token) {
        this();
        setToken(token);
    }

    @Override
    public String inspect() {
        return null;
    }
}
