package objects;

public class AdIntegerObject implements AdObject {
    private AdObjectType type;
    private int value;

    public AdIntegerObject() {
        type = AdObjectType.INT;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    @Override
    public AdObjectType getType() {
        return type;
    }
}
