package ast.nodes;

import ast.AbstractAstNode;
import ast.AstNodeType;
import token.Token;

public class AstProgram extends AbstractAstNode {

    public AstProgram() {
        type = AstNodeType.PROGRAM;
    }

    public AstProgram(Token token) {
        this();
        setToken(token);
    }

    @Override
    public String inspect() {
        return null;
    }
}
