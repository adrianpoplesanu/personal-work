package objects;

public abstract class BNObject {
    private ObjectType type;

    public abstract String inspect();
    public abstract void print();
    public abstract String hash();
    public abstract BNObject copy();

    public ObjectType getType() {
        return type;
    }

    public void setType(ObjectType type) {
        this.type = type;
    }
}
