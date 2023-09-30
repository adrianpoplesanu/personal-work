package ro.adrianus.prototype.ast;

import java.util.ArrayList;
import java.util.List;

public class AstProgram extends AstNode {
    List<AstNode> statements;

    public AstProgram() {
        type = AstNodeTypeEnum.PROGRAM_STATEMENT;
        this.statements = new ArrayList<>();
    }

    @Override
    public String tokenLiteral() {
        return null;
    }

    @Override
    public String toString() {
        return null;
    }

    public void reset() {
        statements.clear();
    }
}
