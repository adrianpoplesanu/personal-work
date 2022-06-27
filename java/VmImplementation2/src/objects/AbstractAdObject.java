package objects;

public abstract class AbstractAdObject implements AdObject {
    protected AdObjectType type;

    @Override
    public AdObjectType getType() {
        return type;
    }
}
