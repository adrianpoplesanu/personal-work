package ast.nodes;

import ast.AstNode;
import ast.AstNodeType;

import java.util.ArrayList;
import java.util.List;

public class AstProgram extends AstNode {
    List<AstNode> statements;

    public AstProgram() {
        type = AstNodeType.PROGRAM;
        statements = new ArrayList<>();
    }

    @Override
    public String tokenLiteral() {
        return null;
    }

    @Override
    public String toString() {
        return null;
    }

    public List<AstNode> getStatements() {
        return statements;
    }

    public void setStatements(List<AstNode> statements) {
        this.statements = statements;
    }

    public void reset() {
        statements.clear();
    }
}
