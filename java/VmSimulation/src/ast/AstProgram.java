package ast;

import java.util.ArrayList;
import java.util.List;

public class AstProgram extends AstNode {
    public List<AstNode> statements = new ArrayList<>();

    public AstProgram() {
        type = AstNodeType.PROGRAM;
    }

    public void reset() {
        statements.clear();
    }
}
