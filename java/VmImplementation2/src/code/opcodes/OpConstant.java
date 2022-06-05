package code.opcodes;

public class OpConstant extends AbstractOpcode {

    public OpConstant() {
        byteCode = (byte) OpcodeEnum.OP_CONSTANT.ordinal();
    }
}
