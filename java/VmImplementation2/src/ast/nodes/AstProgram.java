package ast.nodes;

import ast.AbstractAstNode;
import ast.AstNode;
import ast.AstNodeType;
import token.Token;

import java.util.ArrayList;
import java.util.List;

public class AstProgram extends AbstractAstNode {
    private List<AstNode> statements = new ArrayList<>();

    public AstProgram() {
        type = AstNodeType.PROGRAM;
    }

    public AstProgram(Token token) {
        this();
        setToken(token);
    }

    public void reset() {
        statements.clear();
    }

    @Override
    public String toString() {
        return "AstProgram";
    }

    public List<AstNode> getStatements() {
        return statements;
    }

    public void setStatements(List<AstNode> statement) {
        this.statements = statement;
    }
}
