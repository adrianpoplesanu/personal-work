package chapter3;

public class SinglyLinkedList<E> implements Cloneable {

    private Node<E> head = null;
    private Node<E> tail = null;
    private int size = 0;

    public SinglyLinkedList() {
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public E first() {
        if (isEmpty()) return null;
        return head.getElement();
    }

    public E last() {
        if (isEmpty()) return null;
        return tail.getElement();
    }

    public void addFirst(E e) {
        head = new Node<>(e, head);
        if (size == 0) {
            tail = head;
        }
        size++;
    }

    public void addLast(E e) {
        Node<E> newest = new Node<>(e, null);
        if (isEmpty()) {
            head = newest;
        } else {
            tail.setNext(newest);
        }
        tail = newest;
        size++;
    }

    public E removeFirst() {
        if (isEmpty()) return null;
        E answer = head.getElement();
        head = head.getNext();
        size--;
        if (size == 0) {
            tail = null;
        }
        return answer;
    }

    public boolean equals(Object o) {
        if (o == null) return false;
        if (getClass() != o.getClass()) return false;
        SinglyLinkedList other = (SinglyLinkedList) o;
        if (size != other.size) return false;
        Node walkA = head;
        Node walkB = other.head;
        while (walkA != null) {
            if (!walkA.getElement().equals(walkB.getElement())) return false;
            walkA = walkA.getNext();
            walkB = walkB.getNext();
        }
        return true;
    }

    @Override
    public SinglyLinkedList<E> clone() throws CloneNotSupportedException {
        SinglyLinkedList<E> other = (SinglyLinkedList<E>) super.clone();
        if (size > 0) {
            other.head = new Node<>(head.getElement(), null);
            Node<E> walk = head.getNext();
            Node<E> otherTail = other.head;
            while (walk!= null) {
                Node<E> newest = new Node(walk.getElement(), null);
                otherTail.setNext(newest);
                otherTail = newest;
                walk = walk.getNext();
            }
        }
        return other;
    }

    public void parse() {
        Node<E> walk = head;
        while (walk != null) {
            System.out.print(walk.getElement() + " ");
            walk = walk.getNext();
        }
        System.out.println();
    }

    private static class Node<E> {
        private E element;
        private Node<E> next;

        public Node(E e, Node<E> n) {
            element = e;
            next = n;
        }

        public E getElement() {
            return element;
        }

        public Node<E> getNext() {
            return next;
        }

        public void setNext(Node<E> n) {
            next = n;
        }
    }

    public static void main(String[] args) throws CloneNotSupportedException {
        SinglyLinkedList<Integer> list = new SinglyLinkedList<>();
        list.addFirst(11);
        list.addLast(22);
        list.addFirst(2);

        SinglyLinkedList<Integer> list2 = new SinglyLinkedList<>();
        list2.addFirst(11);
        list2.addLast(22);
        list2.addFirst(2);

        System.out.println(list.equals(list2));

        while(!list.isEmpty()) {
            Integer element = list.removeFirst();
            System.out.println(element);
        }

        list.addLast(1);
        list.addLast(2);
        list.addLast(3);

        SinglyLinkedList<Integer> list3 = list.clone();
        SinglyLinkedList<Integer> list4 = list;
        System.out.println(list.equals(list3));
        System.out.println(list.equals(list4));

        list3.addFirst(77);
        list3.parse();
        list.parse();

        list4.addLast(56);
        list4.parse();
        list.parse();
    }
}
