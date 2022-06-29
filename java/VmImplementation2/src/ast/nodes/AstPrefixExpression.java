package ast.nodes;

import ast.AbstractAstNode;
import ast.AstNodeType;
import token.Token;

public class AstPrefixExpression extends AbstractAstNode {

    public AstPrefixExpression() {
        type = AstNodeType.PREFIX_EXPRESSION;
    }

    public AstPrefixExpression(Token token) {
        this();
        setToken(token);
    }
    @Override
    public String inspect() {
        return null;
    }
}
