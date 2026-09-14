package chapter7;

public class LinkedPositionalList<E> implements PositionalList<E> {
    private static class Node<E> implements Position<E> {
        private E element;
        private Node<E> prev;
        private Node<E> next;
        public Node(E e, Node<E> p, Node<E> n) {
            element = e;
            prev = p;
            next = n;
        }

        @Override
        public E getElement() throws IllegalStateException {
            if (next == null) {
                throw new IllegalStateException("Position no longer valid");
            }
            return element;
        }

        public Node<E> getPrev() {
            return prev;
        }

        public Node<E> getNext() {
            return next;
        }

        public void setElement(E e) {
            element = e;
        }

        public void setPrev(Node<E> p) {
            prev = p;
        }

        public void setNext(Node<E> n) {
            next = n;
        }
    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public Position<E> first() {
        return null;
    }

    @Override
    public Position<E> last() {
        return null;
    }

    @Override
    public Position<E> before(Position<E> p) throws IllegalStateException {
        return null;
    }

    @Override
    public Position<E> after(Position<E> p) throws IllegalStateException {
        return null;
    }

    @Override
    public Position<E> addFirst(E e) {
        return null;
    }

    @Override
    public Position<E> addLast(E e) {
        return null;
    }

    @Override
    public Position<E> addBefore(E e) throws IllegalArgumentException {
        return null;
    }

    @Override
    public Position<E> addAfter(E e) throws IllegalArgumentException {
        return null;
    }

    @Override
    public E set(Position<E> p, E e) throws IllegalArgumentException {
        return null;
    }

    @Override
    public E remove(Position<E> p) throws IllegalArgumentException {
        return null;
    }
}
