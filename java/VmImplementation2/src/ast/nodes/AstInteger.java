package ast.nodes;

import ast.AbstractAstNode;
import ast.AstNodeType;
import token.Token;

public class AstInteger extends AbstractAstNode {
    private int value;
    public AstInteger() {
        type = AstNodeType.INTEGER;
    }
    public AstInteger(Token token) {
        this();
        this.token = token;
    }
    public AstInteger(Token token, int value) {
        this(token);
        this.value = value;
    }
    @Override
    public String toString() {
        return "AstInteger [" + token + "] <" + value + ">";
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }
}
