package adrian2;

public interface LinkedList<E> extends List<E> {
    public E first();
    public E last();
    public void addFirst(E e);
    public void addLast(E e);
}
