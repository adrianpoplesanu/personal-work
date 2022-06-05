package code.opcodes;

public class AbstractOpcode implements Opcode {
    protected byte byteCode;

    @Override
    public byte getByteCode() {
        return byteCode;
    }
}
