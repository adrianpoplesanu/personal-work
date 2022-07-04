package ast.nodes;

import ast.AbstractAstNode;
import ast.AstNodeType;
import token.Token;

public class AstIdent extends AbstractAstNode {
    private String value;
    public AstIdent() {
        type = AstNodeType.IDENT;
    }

    public AstIdent(Token token, String value) {
        this();
        this.token = token;
        this.value = value;
    }

    public AstIdent(Token token) {
        this();
        this.token = token;
    }
    @Override
    public String toString() {
        return "AstIdent [" + token + "] <" + value + ">";
    }
}
