package code.utils;

public class Definition {
    private String name;
    private int[] operandWidths;

    public Definition(String name, int[] operandWidths) {
        this.name = name;
        this.operandWidths = operandWidths;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int[] getOperandWidths() {
        return operandWidths;
    }

    public void setOperandWidths(int[] operandWidths) {
        this.operandWidths = operandWidths;
    }
}
