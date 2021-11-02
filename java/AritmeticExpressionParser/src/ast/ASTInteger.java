package ast;

public class ASTInteger extends ASTNode {
    private String val;

    public ASTInteger(String val) {
        this.val = val;
    }

    public String toString() {
        return val;
    }
}
