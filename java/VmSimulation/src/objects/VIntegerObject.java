package objects;

public class VIntegerObject extends VObject {
    public int value;

    public VIntegerObject(int value) {
        type = VObjectType.INTEGER;
        this.value = value;
    }
}
