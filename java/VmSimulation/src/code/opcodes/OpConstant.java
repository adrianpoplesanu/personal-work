package code.opcodes;

import code.Opcode;

public class OpConstant extends Opcode {
    public OpConstant(byte val) {
        super(val);
        type = OpcodeEnum.OP_CONSTANT;
    }
}
