package ast.nodes;

import ast.AbstractAstNode;
import ast.AstNode;
import ast.AstNodeType;
import token.Token;

public class AstPrefixExpression extends AbstractAstNode {
    private String operator;
    private AstNode right;

    public AstPrefixExpression() {
        type = AstNodeType.PREFIX_EXPRESSION;
    }

    public AstPrefixExpression(Token token) {
        this();
        setToken(token);
    }
    @Override
    public String toString() {
        return "AstPrefixExpression [" + token + "] <" + operator + "> <" + right + ">";
    }

    public String getOperator() {
        return operator;
    }

    public void setOperator(String operator) {
        this.operator = operator;
    }

    public AstNode getRight() {
        return right;
    }

    public void setRight(AstNode right) {
        this.right = right;
    }
}
