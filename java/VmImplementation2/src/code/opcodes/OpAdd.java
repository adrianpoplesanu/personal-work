package code.opcodes;

public class OpAdd extends AbstractOpcode {

    public OpAdd() {
        byteCode = (byte) OpcodeEnum.OP_ADD.ordinal();
    }
}
