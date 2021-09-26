package adrian1;

public interface PositionalList<E> extends List<E> {
	int size();
	boolean isEmpty();
	
	Position<E> first();
	Position<E> last();
	Position<E> before(Position<E> p);
	Position<E> after(Position<E> p);
	
	Position<E> addFirst(E e);
	Position<E> addLast(E e);
	Position<E> addBefore(Position<E> p, E e);
	Position<E> addAfter(Position<E> p, E e);
	E removeFirst();
	E removeLast();
    E set(Position<E> p, E e) throws IllegalArgumentException;
    E remove(Position<E> p) throws IllegalArgumentException;
}
