package heap;

public interface Heap<E> {
    void insert(E e);
    E min();
    E remove();
    void print();
}
