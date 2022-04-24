package ast.nodes;

import ast.AstNode;

import java.util.ArrayList;
import java.util.List;

public class AstProgram extends AstNode {
    List<AstNode> statements;

    public AstProgram() {
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
}
