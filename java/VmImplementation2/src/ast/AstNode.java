package ast;

public interface AstNode {
    AstNodeType getType();

    String inspect();
}
