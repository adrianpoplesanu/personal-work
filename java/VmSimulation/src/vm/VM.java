package vm;

import ast.AstInteger;
import ast.AstProgram;
import code.Code;
import code.Instructions;
import code.Opcode;
import compiler.Bytecode;
import compiler.Compiler;
import objects.VIntegerObject;
import objects.VObject;
import parser.Parser;

import java.util.ArrayList;
import java.util.List;

public class VM {
    public final static int stackSize = 2048;

    public Instructions instructions;
    public List<VObject> constants = new ArrayList<>();

    public VObject[] stack = new VObject[stackSize];
    public int sp;

    public VM() {
        sp = 0;
    }

    public void init(Bytecode bytecode) {
        constants = bytecode.constants;
        instructions = bytecode.instructions;
        stack = new VObject[stackSize];
    }

    public VObject stackTop() {
        if (sp == 0) return null;
        return stack[sp - 1];
    }

    public void run() {
        for (int ip = 0; ip < instructions.instructions.size(); ip++) {
            Opcode op = new Opcode(instructions.instructions.get(ip)); // ???
            switch(op.opcode) {
                case 0:
                    // 0 e OpConstant
                    Code code = new Code();
                    int consIndex = code.readUint16(instructions, ip + 1);
                    ip += 2;
                    push(constants.get(consIndex));
                    break;
                case 1:
                    // 1 e OpAdd
                    VObject right = pop();
                    VObject left = pop();
                    int leftValue = ((VIntegerObject) left).value;
                    int rightValue = ((VIntegerObject) right).value;

                    int result = leftValue + rightValue;
                    push(new VIntegerObject(result));
                    break;
            }
        }
    }

    public void push(VObject obj) {
        if (sp >= stackSize) {
            throw new StackOverflowError("stack limit reached");
        }
        stack[sp++] = obj;
    }

    public VObject pop() {
        VObject obj = stack[sp - 1];
        sp--;
        return obj;
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

        VM vm = new VM();
        vm.init(bytecode);
        vm.run();
        VObject stackElem = vm.stackTop();
        System.out.println(((VIntegerObject) stackElem).value);
    }
}
