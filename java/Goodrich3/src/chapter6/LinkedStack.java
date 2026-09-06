package chapter6;

import chapter3.SinglyLinkedList;

public class LinkedStack<E> implements Stack<E> {
    private SinglyLinkedList<E> list = new SinglyLinkedList<>();

    public LinkedStack() {
    }

    public int size() {
        return list.size();
    }

    public boolean isEmpty() {
        return list.isEmpty();
    }

    public void push(E element) {
        list.addFirst(element);
    }

    public E top() {
        return list.first();
    }

    public E pop() {
        return list.removeFirst();
    }

    public static void main(String[] args) {
        Stack<Integer> stack = new LinkedStack<>();
        System.out.println(stack.isEmpty());
        System.out.println(stack.size());
        stack.push(11);
        stack.push(12);
        stack.push(13);
        System.out.println(stack.isEmpty());
        System.out.println(stack.size());
        System.out.println(stack.top());
        while(!stack.isEmpty()) {
            System.out.print(stack.pop()+ " ");
        }
    }
}
