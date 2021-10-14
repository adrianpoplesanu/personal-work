package adrian1;

import java.util.Iterator;

public class LinkedListPositional<E> implements PositionalList<E>, Iterable<E> {
	
	private static class Node<E> implements Position<E> {
		private Node<E> next;
		private Node<E> prev;
		private E element;
		private boolean valid;
		
		public Node(E e, Node<E> p, Node<E> n) {
			element = e;
			prev = p;
			next = n;
			valid = true;
		}
		
		@Override
		public E getElement() throws IllegalStateException {
			return element;
		}
		
		public void setElement(E e) {
			element = e;
		}
		
		public Node<E> getNext() {
			return next;
		}
		
		public Node<E> getPrev() {
			return prev;
		}
		
		public boolean getValid() {
			return valid;
		}
		
		public void setNext(Node<E> n) {
			next = n;
		}
		
		public void setPrev(Node<E> p) {
			prev = p;
		}
		
		public void setValid(boolean v) {
			valid = v;
		}
	}
	
	private Node<E> head;
	private Node<E> tail;
	private int size = 0;
	
	public LinkedListPositional() {
		head = null;
		tail = null;
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
	public void append(E e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void add(int i, E e) {
		if (i >= size()) {
			addLast(e);
		} else {
			int j = 0;
			Node<E> current = head;
			while(j < i) {
				j++;
				current = (Node<E>) after(current);
			}
			addBetween(e, current.getPrev(), current);
		}
	}

	@Override
	public E get(int i) {
		int j = 0;
		Position<E> result = head;
		while(j < i) {
			result = after(result);
			j++;
		}
		return result.getElement();
	}

	@Override
	public void set(int i, E e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public E remove(int i) {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public Position<E> first() {
		return head;
	}

	@Override
	public Position<E> last() {
		return tail;
	}

	@Override
	public Position<E> before(Position<E> p) throws IllegalArgumentException {
		if (!checkValid(p)) throw new IllegalArgumentException("Invalid position");
		Node<E> node = (Node<E>)p;
		if (node != null) return node.getPrev();
		return null;
	}

	@Override
	public Position<E> after(Position<E> p) throws IllegalArgumentException {
		if (!checkValid(p)) throw new IllegalArgumentException("Invalid position");
		Node<E> node = (Node<E>)p;
		if (node!= null) return node.getNext();
		return null;
	}
	
	private Position<E> addBetween(E e, Node<E> pred, Node<E> succ) {
		Node<E> newest = new Node<E>(e, pred, succ);
		if (pred != null) pred.setNext(newest);
		if (succ != null) succ.setPrev(newest);
		if (pred == null && succ == null) head = tail = newest;
		else if (pred == null) head = newest;
		else if (succ == null) tail = newest;
		size++;
		return newest;
	}
	
	private boolean checkValid(Position<E> p) {
		Node<E> node = (Node<E>)p;
		return node.getValid();
	}
	
	@Override
	public Position<E> addFirst(E e) {
		Position<E> p = addBetween(e, null, head);
		return p;
	}

	@Override
	public Position<E> addLast(E e) {
		Position<E> p = addBetween(e, tail, null);
		return p;
	}
	
	@Override
	public E removeFirst() {
		Position<E> removed = head;
		head = head.getNext();
		head.setPrev(null);
		E result = removed.getElement();
		removed = null;
		return result;
	}

	@Override
	public E removeLast() {
		Position<E> removed = tail;
		tail = tail.getPrev();
		tail.setNext(null);
		E result = removed.getElement();
		removed = null;
		return result;
	}
	
	@Override
	public Position<E> addBefore(Position<E> p, E e) {
		Position<E> pos = addBetween(e, ((Node<E>)p).getPrev(), (Node<E>)p);
		return pos;
	}

	@Override
	public Position<E> addAfter(Position<E> p, E e) {
		Position<E> pos = addBetween(e, (Node<E>)p, ((Node<E>)p).getNext());
		return pos;
	}

	@Override
	public E set(Position<E> p, E e) throws IllegalArgumentException {
		Node<E> node = (Node<E>)p;
		E old = node.getElement();
		node.setElement(e);
		return old;
	}

	@Override
	public E remove(Position<E> p) throws IllegalArgumentException {
		Node<E> node = (Node<E>)p;
		E old = node.getElement();
		Node<E> prev = node.getPrev();
		Node<E> next = node.getNext();
		prev.setNext(next);
		next.setPrev(prev);
		node.setPrev(null);
		node.setNext(null);
		node.setElement(null);
		node.setValid(false);
		size--;
		return old;
	}
	
	@Override
	public Iterator<E> iterator() {
		// TODO Auto-generated method stub
		return null;
	}
}
