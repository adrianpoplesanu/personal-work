package code;

import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Map;

public class Code {

    public Instructions instructions;
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
        Definition def = definitions.get(op);

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

    @Override
    public String toString() {
        return "todo";
    }

    private String fmtInstruction(Definition def, int[] operands) {
        return null;
    }

    private Object[] readOperands(Definition def, Instructions ins) {
        int[] a = {}; // todo
        int b = 5; // todo
        return new Object[] {a, b};
    }

    private int readUint16(Instructions ins) {
        return 0;
    }
}
