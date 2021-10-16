package adrian2;

import java.util.Iterator;

public class DoubleLinkedList<E> implements LinkedList<E>, Iterable<E> {
	
	private class Node<E> {
		private E value;
		private Node<E> prev;
		private Node<E> next;
		
		public E getValue() {
			return value;
		}
		public void setValue(E value) {
			this.value = value;
		}
		public Node<E> getPrev() {
			return prev;
		}
		public void setPrev(Node<E> prev) {
			this.prev = prev;
		}
		public Node<E> getNext() {
			return next;
		}
		public void setNext(Node<E> next) {
			this.next = next;
		}
	}
	
	private Node<E> head;
	private Node<E> tail;
	private int size = 0;

	@Override
	public int size() {
		// TODO Auto-generated method stub
		return size;
	}

	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		return size == 0;
	}

	@Override
	public void add(int i, E e) {
		Node<E> new_node = new Node<E>();
		new_node.setValue(e);
		if (tail == null) {
			new_node.setNext(null);
			new_node.setPrev(null);
			head = tail = new_node;
		} else {
			tail.setNext(new_node);
			new_node.setPrev(tail);
			tail = new_node;
		}
	}

	@Override
	public E get(int i) {
		Node<E> current = head;
		while(i-- > 0) {
			current = head.getNext();
		}
		return current.getValue();
	}

	@Override
	public E set(int i, E e) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public E remove(int i) {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public E first() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public E last() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void addFirst(E e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void addLast(E e) {
		// TODO Auto-generated method stub
		
	}
	
	private class DoubleLinkedListIterator implements Iterator<E> {

		@Override
		public boolean hasNext() {
			// TODO Auto-generated method stub
			return false;
		}

		@Override
		public E next() {
			// TODO Auto-generated method stub
			return null;
		}
		
	}

	@Override
	public Iterator<E> iterator() {
		return new DoubleLinkedListIterator();
	}
}
