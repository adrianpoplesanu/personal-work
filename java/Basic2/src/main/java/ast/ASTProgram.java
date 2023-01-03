package ast;

import java.util.ArrayList;
import java.util.List;

public class ASTProgram extends AbstractASTNode {
    private List<ASTNode> statements;

    public ASTProgram() {
        type = ASTNodeTypeEnum.PROGRAM;
        statements = new ArrayList<>();
    }
    @Override
    public ASTNodeTypeEnum getType() {
        return type;
    }

    @Override
    public String inspect() {
        return null;
    }

    public List<ASTNode> getStatements() {
        return statements;
    }

    public void setStatements(List<ASTNode> statements) {
        this.statements = statements;
    }
}
