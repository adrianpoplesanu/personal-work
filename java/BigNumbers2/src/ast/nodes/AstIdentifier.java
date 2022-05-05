package ast.nodes;

import ast.AstNode;
import ast.AstNodeType;
import token.Token;
import token.TokenType;

public class AstIdentifier extends AstNode {
    private Token token;

    public AstIdentifier() {
        type = AstNodeType.IDENT;
    }

    public AstIdentifier(Token token) {
        this();
        this.token = token;
    }

    @Override
    public String tokenLiteral() {
        return token.getTokenLiteral();
    }

    @Override
    public String toString() {
        return "AstNode [Identifier]";
    }
}
