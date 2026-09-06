package chapter6;

import chapter3.SinglyLinkedList;

public class LinkedQueue<E> implements Queue<E> {
    private SinglyLinkedList<E> list = new SinglyLinkedList<>();

    @Override
    public int size() {
        return list.size();
    }

    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }

    @Override
    public void enqueue(E e) {
        list.addLast(e);
    }

    @Override
    public E first() {
        return list.first();
    }

    @Override
    public E dequeue() {
        return list.removeFirst();
    }

    public static void main(String[] args) {
        Queue<Integer> queue = new LinkedQueue<>();

        System.out.println(queue.isEmpty());
        System.out.println(queue.size());
        queue.enqueue(11);
        queue.enqueue(21);
        queue.enqueue(31);

        System.out.println(queue.isEmpty());
        System.out.println(queue.size());

        while(!queue.isEmpty()) {
            System.out.print(queue.dequeue() + " ");
        }
    }
}
