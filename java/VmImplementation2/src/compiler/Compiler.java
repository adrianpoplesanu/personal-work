package compiler;

import ast.AstNode;
import ast.nodes.AstExpressionStatement;
import ast.nodes.AstInfixExpression;
import ast.nodes.AstInteger;
import ast.nodes.AstProgram;
import code.Code;
import code.opcodes.OpAdd;
import code.opcodes.OpConstant;
import code.opcodes.Opcode;
import objects.AdIntegerObject;
import objects.AdObject;

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
                compile(((AstExpressionStatement) node).getExpression());
            case INFIX_EXPRESSION:
                AstInfixExpression infixExpression = (AstInfixExpression) node;
                compile(infixExpression.getLeft());
                compile(infixExpression.getRight());
                switch(infixExpression.getOperator()) {
                    case "+":
                        emit(new OpAdd());
                        break;
                }
            case PREFIX_EXPRESSION:
                break;
            case INTEGER:
                AstInteger astInteger = (AstInteger) node;
                AdIntegerObject integer = new AdIntegerObject(astInteger.getValue());
                emit(new OpConstant(), addConstant(integer));
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

    private int addConstant(AdObject obj) {
        //...
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
