package objects;

public class B2IntegerObject implements B2Object {
    private B2ObjectTypeEnum type;
    private int value;

    public B2IntegerObject() {
        type = B2ObjectTypeEnum.INTEGER;
    }
    @Override
    public String inspect() {
        return String.valueOf(value);
    }

    public B2ObjectTypeEnum getType() {
        return type;
    }

    public void setType(B2ObjectTypeEnum type) {
        this.type = type;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }
}
