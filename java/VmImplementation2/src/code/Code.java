package code;

import code.opcodes.OpAdd;
import code.opcodes.OpConstant;
import code.opcodes.Opcode;
import code.opcodes.OpcodeEnum;
import code.utils.Definition;
import code.utils.Instructions;
import code.utils.Operands;

import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Map;

public class Code {

    private Instructions instructions = new Instructions();

    private Map<Byte, Definition> definitionsMap = new HashMap<>();

    public Code() {
        definitionsMap.put((byte) OpcodeEnum.OP_CONSTANT.ordinal(), new Definition("OpConstant", new int[]{2} ));
        definitionsMap.put((byte) OpcodeEnum.OP_ADD.ordinal(), new Definition("OpAdd", new int[]{} ));
    }

    public Definition lookup(byte op) {
        return definitionsMap.get(op);
    }

    public byte[] make(Opcode op, int... operands) {
        Definition definition = lookup(op.getByteCode());

        int instructionLen = 1;
        for (int w : definition.getOperandWidths()) {
            instructionLen += w;
        }

        byte[] instruction = new byte[instructionLen];
        instruction[0] = op.getByteCode();

        int offset = 1;
        int i = 0;
        for (int o : operands) {
            int width = definition.getOperandWidths()[i++];
            switch (width) {
                case 2:
                    ByteBuffer b = ByteBuffer.allocate(4);
                    b.putInt(o);
                    byte[] result = b.array();
                    instruction[offset] = result[2];
                    instruction[offset + 1] = result[3];
                    break;
            }
            offset += width;
        }

        return instruction;
    }

    public String print() {
        String out = "";
        int i = 0;
        while(i < instructions.size()) {
            Definition definition = lookup(instructions.get(i));
            Operands res = readOperands(definition, instructions, i + 1);
            int[] operands = res.getOperands();
            int read = res.getOffset();
            out += String.format("%04d %s\n", i, formatInstruction(definition, operands));
            i += 1 + read;
        }
        return out;
    }

    private Operands readOperands(Definition definition, Instructions instructions, int start) {
        int[] operands = new int[definition.getOperandWidths().length];
        int offset = 0;

        int i = 0;
        for (int width : definition.getOperandWidths()) {
            switch (width) {
                case 2:
                    operands[i++] = readUint16(instructions, start + offset);
                    break;
            }
            offset += width;
        }
        //return new Object[] {operands, offset};
        return new Operands(operands, offset);
    }

    private int readUint16(Instructions instructions, int offset) {
        byte[] result = {0, 0, instructions.get(offset), instructions.get(offset + 1)};
        return ByteBuffer.wrap(result).getInt();
    }

    private String formatInstruction(Definition definition, int[] operands) {
        int operandCount = definition.getOperandWidths().length;
        switch (operandCount) {
            case 0:
                return definition.getName();
            case 1:
                return String.format("%s %d", definition.getName(), operands[0]);
        }
        return String.format("ERROR: unhandled operandCount for %s\n", definition.getName());
    }

    public static void main(String[] args) {
        System.out.println("testing code...");

        Code code = new Code();
        byte[][] instructions = {
                code.make(new OpAdd()),
                code.make(new OpConstant(), 2),
                code.make(new OpConstant(), 65535)
        };

        for (int i = 0; i < instructions.length; i++) {
            for (int j = 0; j < instructions[i].length; j++) {
                code.instructions.add(instructions[i][j]);
            }
        }
        System.out.println(code.print());
    }
}
