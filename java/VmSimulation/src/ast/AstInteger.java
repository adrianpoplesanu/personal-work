package ast;

import token.Token;

public class AstInteger extends AstNode {
    public Token token;
    public int value;

    public AstInteger(Token token, int value) {
        this.token = token;
        this.value = value;
    }

    public String toString() {
        return "[AstInteger] <" + value + ">";
    }
}
