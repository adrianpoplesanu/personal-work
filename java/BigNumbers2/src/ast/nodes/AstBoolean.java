package ast.nodes;

import ast.AstNode;
import ast.AstNodeType;

public class AstBoolean extends AstNode {
    private boolean value;

    public AstBoolean() {
        type = AstNodeType.BOOLEAN;
    }

    public AstBoolean(boolean value) {
        this();
        this.value = value;
    }

    @Override
    public String tokenLiteral() {
        return null;
    }

    @Override
    public String toString() {
        return null;
    }
}
