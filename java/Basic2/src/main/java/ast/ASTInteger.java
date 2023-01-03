package ast;

import token.Token;

public class ASTInteger extends AbstractASTNode {
    private int value;

    public ASTInteger(Token token) {
        this.token = token;
        type = ASTNodeTypeEnum.INTEGER;
    }

    @Override
    public ASTNodeTypeEnum getType() {
        return type;
    }

    @Override
    public String inspect() {
        return String.valueOf(value);
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }
}
