package ast;

public interface ASTNode {
    ASTNodeTypeEnum getType();
    String inspect();
}
