package objects;

public class AdIntegerObject implements AdObject {
    private AdObjectType type;
    private int value;

    public AdIntegerObject() {
        type = AdObjectType.INT;
    }

    public AdIntegerObject(int value) {
        this();
        this.value = value;
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
