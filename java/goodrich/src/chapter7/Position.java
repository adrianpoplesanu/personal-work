package chapter7;

public interface Position<E> {
    E getElement() throws IllegalStateException;
}
