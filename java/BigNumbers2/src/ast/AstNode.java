package ast;

public abstract class AstNode {
    protected AstNodeType type;
    public abstract String tokenLiteral();
    public abstract String toString();
}
