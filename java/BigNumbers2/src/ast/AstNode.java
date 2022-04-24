package ast;

public abstract class AstNode {
    private AstNodeType type;
    public abstract String tokenLiteral();
    public abstract String toString();
}
