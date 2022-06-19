package ast;

import token.Token;

public abstract class AbstractAstNode implements AstNode {
    protected AstNodeType type;
    protected Token token;

    @Override
    public AstNodeType getType() {
        return type;
    }

    public void setType(AstNodeType type) {
        this.type = type;
    }

    public Token getToken() {
        return token;
    }

    public void setToken(Token token) {
        this.token = token;
    }
}
