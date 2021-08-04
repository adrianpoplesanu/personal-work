package chapter6;

import chapter3.SinglyLinkedList;

public class LinkedListStack<E> implements Stack<E> {
	private SinglyLinkedList<E> list = new SinglyLinkedList<E>();

	@Override
	public int size() {
		return list.size();
	}

	@Override
	public boolean isEmpty() {
		return list.isEmpty();
	}

	@Override
	public void push(E e) {
		list.AddFirst(e);
	}

	@Override
	public E top() {
		return list.first();
	}

	@Override
	public E pop() {
		return list.removeFirst();
	}

}
