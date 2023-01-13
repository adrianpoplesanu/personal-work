package code.opcodes;

import code.Opcode;

public class OpAdd extends Opcode {
    public OpAdd(byte val) {
        super(val);
        type = OpcodeEnum.OP_ADD;
    }
}
