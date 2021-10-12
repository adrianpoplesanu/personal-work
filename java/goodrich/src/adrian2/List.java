package adrian2;

public interface List<E> {
	int size();
	boolean isEmpty();
	
    public void add(int i, E e);
    public E get(int i);
    public E set(int i, E e);
    public E remove(int i);
}
