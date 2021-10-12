package adrian2;

public interface PositionalList<E> extends LinkedList<E> {
	public void addAfter(Position<E> p, E e);
    public void addBefore(Position<E> p, E e);
}
