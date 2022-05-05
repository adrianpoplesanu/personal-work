package ast.nodes;

import ast.AstNode;
import ast.AstNodeType;
import token.Token;

public class AstLetStatement extends AstNode {
    private Token token;
    private AstNode name;
    private AstNode value;

    public AstLetStatement() {
        type = AstNodeType.LET_STATEMENT;
    }

    public AstLetStatement(Token token) {
        this();
        this.token = token;
    }

    @Override
    public String tokenLiteral() {
        return token.getTokenLiteral();
    }

    @Override
    public String toString() {
        return "AstNode [LetStatement]";
    }

    public AstNode getName() {
        return name;
    }

    public void setName(AstNode name) {
        this.name = name;
    }

    public AstNode getValue() {
        return value;
    }

    public void setValue(AstNode value) {
        this.value = value;
    }
}
