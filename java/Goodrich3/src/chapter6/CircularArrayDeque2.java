package chapter6;

public class CircularArrayDeque2<E> implements Deque<E> {
    public static final int CAPACITY = 1000;
    private E[] data;
    private int f = 0;
    private int sz = 0;

    public CircularArrayDeque2() {
        this(CAPACITY);
    }

    public CircularArrayDeque2(int capacity) {
        data = (E[]) new Object[capacity];
    }

    @Override
    public int size() {
        return sz;
    }

    @Override
    public boolean isEmpty() {
        return sz == 0;
    }

    @Override
    public E first() {
        if (isEmpty()) return null;
        return data[f];
    }

    @Override
    public E last() {
        if (isEmpty()) return null;
        return data[(f + sz - 1) % data.length];
    }

    @Override
    public void addFirst(E e) {
        if (sz == data.length) throw new IllegalStateException("Deque is full");
        f = (f - 1 + data.length) % data.length;
        data[f] = e;
        sz++;
    }

    @Override
    public void addLast(E e) {
        if (sz == data.length) throw new IllegalStateException("Deque is full");
        int avail = (f + sz) % data.length;
        data[avail] = e;
        sz++;
    }

    @Override
    public E removeFirst() {
        if (isEmpty()) return null;
        E answer = data[f];
        data[f] = null;
        f = (f + 1) % data.length;
        sz--;
        return answer;
    }

    @Override
    public E removeLast() {
        if (isEmpty()) return null;
        int idx = (f + sz - 1) % data.length;
        E answer = data[idx];
        data[idx] = null;
        sz--;
        return answer;
    }

    public static void main(String[] args) {
        CircularArrayDeque2<Integer> deque = new CircularArrayDeque2<>();
        deque.addFirst(11);
        deque.removeLast();

        deque.addFirst(12);
        deque.removeFirst();

        deque.addLast(13);
        deque.removeFirst();

        deque.addLast(14);
        deque.removeLast();

        deque.addFirst(1);
        deque.addFirst(2);
        deque.addFirst(3);
        while(!deque.isEmpty()) {
            System.out.println(deque.removeLast());
        }

        deque.addLast(41);
        deque.addLast(42);
        deque.addLast(43);
        while(!deque.isEmpty()) {
            System.out.println(deque.removeFirst());
        }
    }
}
