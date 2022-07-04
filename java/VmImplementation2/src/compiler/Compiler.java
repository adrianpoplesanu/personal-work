package compiler;

import ast.AstNode;
import ast.nodes.AstProgram;
import code.Code;
import code.opcodes.Opcode;

public class Compiler {
    private Bytecode bytecode;
    private Code code;

    public Compiler() {
        bytecode = new Bytecode();
        code = new Code();
    }

    public void init() {
        bytecode = new Bytecode();
    }

    public void compile(AstNode node) {
        switch(node.getType()) {
            case PROGRAM:
                AstProgram program = (AstProgram) node;
                for (AstNode stmt : program.getStatements()) {
                    compile(stmt);
                }
            case EXPRESSION_STATEMENT:
                break;
            case INFIX_EXPRESSION:
                break;
            case PREFIX_EXPRESSION:
                break;
            case INTEGER:
                break;
            case IDENT:
                break;
        }
    }

    public int emit(Opcode opcode, int... operands) {
        byte[] ins = code.make(opcode, operands);
        int pos = addInstruction(ins);
        return pos;
    }

    private int addInstruction(byte[] ins) {
        return 0;
    }

    public Bytecode getBytecode() {
        return bytecode;
    }

    public void setBytecode(Bytecode bytecode) {
        this.bytecode = bytecode;
    }

    public static void main(String[] args) {
        System.out.println("testing compiler");
    }
}
