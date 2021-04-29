package chapter3;

public class CircularyLinkedList<E> {
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
	
	private Node<E> tail = null;
	private int size = 0;
	
	public CircularyLinkedList() {
		
	}
	
	public int getSize() {
		return size;
	}
	
	public boolean isEmpty() {
		return size == 0;
	}

	public E first() {
		return tail.getNext().getElement();
	}
	
	public E last() {
		return tail.getElement();
	}
	
	public void rotate() {
		if (tail != null) {
			tail = tail.getNext();
		}
	}
	
	public void addFirst(E e) {
		Node<E> newest = new Node<E>(e, null);
		if (isEmpty()) {
			tail = newest;
		} else {
			newest.setNext(tail.getNext());
			tail.setNext(newest);
		}
		size++;
	}
	
	public void addLast(E e) {
		Node<E> newest = new Node<E>(e, null);
		if (isEmpty()) {
			tail = newest;
		} else {
			newest.setNext(tail.getNext());
			tail.setNext(newest);
			rotate();
		}
		size++;
	}
	
	public E removeFirst() {
		if (isEmpty()) return null;
		Node<E> head = tail.getNext();
		if (head == tail) tail = null;
		else {
			tail.setNext(head.getNext());
		}
		size--;
		return head.getElement();
	}
}
