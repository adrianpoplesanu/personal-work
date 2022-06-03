package code;

import code.opcodes.OpcodeEnum;

public class Opcode {
    public byte opcode;

    protected OpcodeEnum type;

    public Opcode (byte val) {
        opcode = val;
    }
}
