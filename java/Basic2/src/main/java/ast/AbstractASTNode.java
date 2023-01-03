package ast;

import token.Token;

public abstract class AbstractASTNode implements ASTNode {
    protected ASTNodeTypeEnum type;
    protected Token token;
}
