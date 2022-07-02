package ast.nodes;

import ast.AbstractAstNode;
import ast.AstNodeType;
import token.Token;

public class AstIdent extends AbstractAstNode {
    private String value;
    public AstIdent() {
        type = AstNodeType.IDENT;
    }

    public AstIdent(Token token) {
        this();
        this.token = token;
    }
    @Override
    public String inspect() {
        return "AstIdent [" + token + "] <" + value + ">";
    }
}
