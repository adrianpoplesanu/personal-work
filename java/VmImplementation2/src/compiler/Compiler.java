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
import code.utils.Instructions;
import objects.AdIntegerObject;
import objects.AdObject;
import parser.Parser;

import java.util.ArrayList;
import java.util.List;

public class Compiler {
    private Instructions instructions;
    private Bytecode bytecode;
    private Code code;
    private List<AdObject> constants;

    public Compiler() {
        instructions = new Instructions();
        bytecode = new Bytecode();
        code = new Code();
        constants = new ArrayList<>();
    }

    public void init() {
        instructions = new Instructions();
        bytecode = new Bytecode();
    }

    public void compile(AstNode node) {
        switch(node.getType()) {
            case PROGRAM:
                AstProgram program = (AstProgram) node;
                for (AstNode stmt : program.getStatements()) {
                    compile(stmt);
                }
                break;
            case EXPRESSION_STATEMENT:
                compile(((AstExpressionStatement) node).getExpression());
                break;
            case INFIX_EXPRESSION:
                AstInfixExpression infixExpression = (AstInfixExpression) node;
                compile(infixExpression.getLeft());
                compile(infixExpression.getRight());
                switch(infixExpression.getOperator()) {
                    case "+":
                        emit(new OpAdd());
                        break;
                }
                break;
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
        int posNewInstruction = instructions.size();
        for (byte b : ins) {
            instructions.add(b);
        }
        return posNewInstruction;
    }

    private int addConstant(AdObject obj) {
        constants.add(obj);
        return constants.size() - 1;
    }

    public Bytecode getBytecode() {
        bytecode.setInstructions(instructions);
        bytecode.setConstants(constants);
        return bytecode;
    }

    public void setBytecode(Bytecode bytecode) {
        this.bytecode = bytecode;
    }

    public Instructions getInstructions() {
        return instructions;
    }

    public void setInstructions(Instructions instructions) {
        this.instructions = instructions;
    }

    public Code getCode() {
        return code;
    }

    public void setCode(Code code) {
        this.code = code;
    }

    public List<AdObject> getConstants() {
        return constants;
    }

    public void setConstants(List<AdObject> constants) {
        this.constants = constants;
    }

    public static void main(String[] args) {
        System.out.println("testing compiler");

        Compiler compiler = new Compiler();

        Parser parser = new Parser();
        parser.load("1+2");
        AstProgram program = new AstProgram();
        program.reset();
        parser.buildStatements(program);
        compiler.init();
        compiler.compile(program);
        Bytecode bytecode = compiler.getBytecode();
        compiler.getCode().setInstructions(bytecode.getInstructions());
        System.out.println(compiler.getCode().print());
    }
}
