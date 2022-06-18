package compiler;

public class Compiler {
    private Bytecode bytecode;

    public Compiler() {
        bytecode = new Bytecode();
    }

    public void init() {
        bytecode = new Bytecode();
    }

    public Bytecode getBytecode() {
        return bytecode;
    }

    public void setBytecode(Bytecode bytecode) {
        this.bytecode = bytecode;
    }
}
