package vm;

import code.Code;
import code.opcodes.Opcode;
import code.utils.Instructions;
import compiler.Bytecode;
import objects.AdIntegerObject;
import objects.AdObject;

import java.util.ArrayList;
import java.util.List;

public class VM {
    public final static int stackSize = 2048;
    public Instructions instructions;
    public List<AdObject> constants = new ArrayList<>();
    public AdObject[] stack = new AdObject[stackSize];
    public int sp;

    public VM() {
        sp = 0;
    }

    public void init(Bytecode bytecode) {
        constants = bytecode.getConstants();
        instructions = bytecode.getInstructions();
        stack = new AdObject[stackSize];
    }

    public AdObject stackTop() {
        if (sp == 0) return null;
        return stack[sp - 1];
    }

    public void run() {
        for (int ip = 0; ip < instructions.getInstructions().size(); ip++) {
            //Opcode op = new Opcode(instructions.getInstructions().get(ip)); // ???
            byte opcode = instructions.getInstructions().get(ip);
            switch(opcode) {
                case 0:
                    // 0 e OpConstant
                    Code code = new Code();
                    int consIndex = code.readUint16(instructions, ip + 1);
                    ip += 2;
                    push(constants.get(consIndex));
                    break;
                case 1:
                    // 1 e OpAdd
                    AdObject right = pop();
                    AdObject left = pop();
                    int leftValue = ((AdIntegerObject) left).getValue();
                    int rightValue = ((AdIntegerObject) right).getValue();

                    int result = leftValue + rightValue;
                    push(new AdIntegerObject(result));
                    break;
            }
        }
    }

    public void push(AdObject obj) {
        if (sp >= stackSize) {
            throw new StackOverflowError("stack limit reached");
        }
        stack[sp++] = obj;
    }

    public AdObject pop() {
        AdObject obj = stack[sp - 1];
        sp--;
        return obj;
    }
}
