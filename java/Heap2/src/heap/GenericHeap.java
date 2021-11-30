package heap;

public class GenericHeap<E> implements Heap<E> {

    private class Node<E> {
        private E element;

        public Node(E e) {
            element = e;
        }

        public E getElement() {
            return element;
        }

        public void setElement(E e) {
            element = e;
        }
    }

    private Node<E>[] heap;
    int size;

    public GenericHeap() {
        size = 0;
        heap = new Node[100];
    }

    private int compare(E e1, E e2) {
        return ((Comparable<E>) e1).compareTo(e2);
    }

    @Override
    public void insert(E e) {
        heap[size++] = new Node<>(e);
        int poz = size - 1;
        while((poz - 1) / 2 >= 0 && compare(heap[(poz - 1) / 2].getElement(), heap[poz].getElement()) > 0) {
            E aux = heap[poz].getElement();
            heap[poz].setElement(heap[(poz - 1) / 2].getElement());
            heap[(poz - 1) / 2].setElement(aux);
            poz = (poz - 1) / 2;
        }
    }

    @Override
    public E min() {
        return heap[0].getElement();
    }

    @Override
    public E remove() {
        E result = heap[0].getElement();
        int poz = 0;
        boolean has_children;
        while (poz < size) {
            has_children = false;
            E minValue = null;
            int next = -12;
            if (poz * 2 + 1 < size) {
                minValue = heap[poz * 2 + 1].getElement();
                next = poz * 2 + 1;
                has_children = true;
            }
            if (poz * 2 + 2 < size) {
                if (compare(heap[poz * 2 + 2].getElement(), minValue) < 0) {
                    minValue = heap[poz * 2 + 2].getElement();
                    next = poz * 2 + 2;
                    has_children = true;
                }
            }
            if (!has_children) {
                for (int i = poz; i < size - 1; i++) heap[i] = heap[i + 1];
                break;
            }
            heap[poz].setElement(minValue);
            poz = next;
        }
        size--;
        return result;
    }

    @Override
    public void print() {
        for (int i = 0; i < size; i++) System.out.print(heap[i].getElement() + " ");
        System.out.println("");
    }
}
