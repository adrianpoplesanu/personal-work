package code;

import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Map;

public class Code {

    public Instructions instructions = new Instructions();
    private byte iota = 0;

    private Opcode OpConstant = new Opcode(iota++);
    private Opcode OpAdd = new Opcode(iota++);
    private Map<Byte, Definition> definitions = new HashMap<>();

    public Code () {
        definitions.put(OpConstant.opcode, new Definition("OpConstant", new int[] {2}));
        definitions.put(OpAdd.opcode, new Definition("OpAdd", new int[]{}));
    }

    public Definition lookup(byte op) {
        return definitions.get(op);
    }

    public byte[] make(Opcode op, int... operands) {
        Definition def = definitions.get(op.opcode);

        int instructionLen = 1;
        for (int w : def.operandWidths) {
            instructionLen += w;
        }

        byte[] instruction = new byte[instructionLen];
        instruction[0] = op.opcode;

        int offset = 1;
        int i = 0;
        for (int o : operands) {
            int width = def.operandWidths[i++];
            switch (width) {
                case 2:
                    // aici e ceva cu big endian, great
                    ByteBuffer b = ByteBuffer.allocate(4); // int has 4 bytes, ignore first 2 for int16
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
        while (i < instructions.instructions.size()) {
            Definition def = lookup(instructions.instructions.get(i));
            Object[] res = readOperands(def, instructions, i + 1);
            int[] operands;
            int read;
            operands = (int[]) res[0];
            read = (int) res[1];
            //System.out.println("some formatting here");
            out += String.format("%04d %s\n", i, fmtInstruction(def, operands));
            i += 1 + read;
        }
        return out;
    }

    private String fmtInstruction(Definition def, int[] operands) {
        int operandCount = def.operandWidths.length;
        switch (operandCount) {
            case 0:
                return def.name;
            case 1:
                return String.format("%s %d", def.name, operands[0]);
        }
        return String.format("ERROR: unhandled operandCount for %s\n", def.name);
    }

    private Object[] readOperands(Definition def, Instructions ins, int i) {
        int[] operands = new int[def.operandWidths.length];
        int offset = 0;

        int j = 0;
        for (int width : def.operandWidths) {
            switch (width) {
                case 2:
                    operands[j++] = (int) readUint16(ins, offset + i);
            }
            offset += width;
        }

        return new Object[] {operands, offset};
    }

    private int readUint16(Instructions ins, int offset) {
        // https://mkyong.com/java/java-convert-byte-to-int-and-vice-versa/
        ByteBuffer b = ByteBuffer.allocate(4); // int has 4 bytes, ignore first 2 for int16
        byte[] result = {0, 0, ins.instructions.get(offset), ins.instructions.get(offset + 1)};
        return ByteBuffer.wrap(result).getInt();
    }

    public static void main(String[] args) {
        Code code = new Code();
        byte[][] instructions = {
            code.make(code.OpAdd),
            code.make(code.OpConstant, 2),
            code.make(code.OpConstant, 65535)
        };

        for (int i = 0; i < instructions.length; i++) {
            for (int j = 0; j < instructions[i].length; j++) {
                //System.out.print(instructions[i][j] + " ");
                code.instructions.instructions.add(instructions[i][j]);
            }
        }
        System.out.println(code.print());
    }
}
