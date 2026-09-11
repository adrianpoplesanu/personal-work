package chapter6;

public class CircularArrayDeque<E> implements Deque<E> {
    private static final int CAPACITY = 1000;
    private E[] data;
    private int h = 0;
    private int t = 0;
    private int size = 0;
    private int capacity;

    public CircularArrayDeque() {
        this(CAPACITY);
        capacity = CAPACITY;
    }

    public CircularArrayDeque(int capacity) {
        data = (E[]) new Object[capacity];
        this.capacity = capacity;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public E first() {
        if (isEmpty()) return null;
        return data[h];
    }

    @Override
    public E last() {
        if (isEmpty()) return null;
        return data[t];
    }

    @Override
    public void addFirst(E e) {
        if (isEmpty()) {
            data[h] = e;
            t = h;
        } else {
            if ((h - 1 + capacity) % capacity == t) {
                throw new IllegalStateException("Deque is full");
            }
            h--;
            h = (h + capacity) % capacity;
            data[h] = e;
        }
        size++;
    }

    @Override
    public void addLast(E e) {
        if (isEmpty()) {
            data[h] = e;
            t = h;
        } else {
            if ((t + 1 + capacity) % capacity == h) {
                throw new IllegalStateException("Deque is full");
            }
            t++;
            t = (t + capacity) % capacity;
            data[t] = e;
        }
        size++;
    }

    @Override
    public E removeFirst() {
        if (isEmpty()) return null;
        E answer = data[h];
        data[h] = null;
        h++;
        h = (h + capacity) % capacity;
        size--;
        return answer;
    }

    @Override
    public E removeLast() {
        if (isEmpty()) return null;
        E answer = data[t];
        data[t] = null;
        t--;
        t = (t + capacity) % capacity;
        size--;
        return answer;
    }

    public static void main(String[] args) {
        CircularArrayDeque<Integer> deque = new CircularArrayDeque<>();
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
