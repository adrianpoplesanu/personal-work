package chapter7;

public interface PositionalList<E> {
    int size();
    boolean isEmpty();
    Position<E> first();
    Position<E> last();
    Position<E> before(Position<E> p) throws IllegalStateException;
    Position<E> after(Position<E> p) throws IllegalStateException;
    Position<E> addFirst(E e);
    Position<E> addLast(E e);
    Position<E> addBefore(E e) throws IllegalArgumentException;
    Position<E> addAfter(E e) throws IllegalArgumentException;
    E set(Position<E> p, E e) throws IllegalArgumentException;
    E remove(Position<E> p) throws IllegalArgumentException;
}
