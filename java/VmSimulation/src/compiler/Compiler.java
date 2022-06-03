package compiler;

import ast.*;
import code.Code;
import code.Instructions;
import code.Opcode;
import objects.VIntegerObject;
import objects.VObject;
import parser.Parser;

import java.util.ArrayList;
import java.util.List;

public class Compiler {
    public Instructions instructions;
    public List<VObject> constants;

    public Compiler () {
        instructions = new Instructions();
        constants = new ArrayList<>();
    }

    public void init() {
        instructions = new Instructions();
        constants = new ArrayList<>();
    }

    public void compile(AstNode node) {
        switch(node.type) {
            case PROGRAM:
                AstProgram expr = (AstProgram) node;
                for (AstNode stmt : expr.statements) {
                    compile(stmt);
                }
                break;
            case EXPRESSION_STATEMENT:
                AstExpressionStatement stmt = (AstExpressionStatement) node;
                compile(stmt.getExpression());
                break;
            case INFIX_EXPRESSION:
                AstInfixExpression expr2 = (AstInfixExpression) node; // fix name expr2, it sucks
                compile(expr2.left);
                compile(expr2.right);
                switch(expr2.operator) {
                    case "+":
                        //emit(code.OpAdd);
                        Code c = new Code();
                        emit(c.OpAdd); // this is bad, i need to have OpAdd extend Opcode and use Opcode here
                        break;
                }
                break;
            case INTEGER:
                AstInteger astInteger = (AstInteger) node;
                VIntegerObject integer = new VIntegerObject(astInteger.value);
                Code c = new Code();
                emit(c.OpConstant, addConstant(integer));
                break;
            case PREFIX_EXPRESSION:
                break;
        }
    }

    public Bytecode bytecode() {
        Bytecode result = new Bytecode();
        result.instructions = instructions;
        result.constants = constants;
        return result;
    }

    public int addConstant(VObject obj) {
        constants.add(obj);
        return constants.size() - 1;
    }

    public int emit(Opcode op, int... operands) {
        Code c = new Code();
        byte[] ins = c.make(op, operands);
        int pos = addInstruction(ins);
        return pos;
    }

    public int addInstruction(byte[] ins) {
        int posNewInstruction = instructions.instructions.size();
        for (byte b : ins) {
            instructions.instructions.add(b);
        }
        return posNewInstruction;
    }

    public static void main(String[] args) {
        Compiler compiler = new Compiler();

        Parser parser = new Parser();
        parser.load("1+2");
        AstProgram program = new AstProgram();
        program.reset();
        parser.buildProgramStatements(program);
        compiler.init();
        compiler.compile(program);
        Bytecode bytecode = compiler.bytecode();
        //System.out.println(bytecode);
        Code code = new Code();
        code.instructions = bytecode.instructions;
        System.out.println(code.print());
    }
}
