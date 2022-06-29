package code.utils;

public class Operands {
    private int[] operands;
    private int offset;

    public Operands(int[] operands, int offset) {
        this.operands = operands;
        this.offset = offset;
    }

    public int[] getOperands() {
        return operands;
    }

    public void setOperands(int[] operands) {
        this.operands = operands;
    }

    public int getOffset() {
        return offset;
    }

    public void setOffset(int offset) {
        this.offset = offset;
    }
}
