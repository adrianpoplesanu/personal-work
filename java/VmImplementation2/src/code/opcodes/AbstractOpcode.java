package code.opcodes;

public abstract class AbstractOpcode implements Opcode {
    protected byte byteCode;

    @Override
    public byte getByteCode() {
        return byteCode;
    }
}
