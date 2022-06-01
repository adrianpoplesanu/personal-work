package ast;

import token.Token;

public class AstPrefixExpression extends AstNode {
    public Token token;
    public String operator;
    public AstNode right;

    public String toString() {
        return "[AstPrefixExpression] <" + operator + "> <" + right + ">";
    }
}
