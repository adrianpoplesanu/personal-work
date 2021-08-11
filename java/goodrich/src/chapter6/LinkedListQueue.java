package chapter6;

import chapter3.SinglyLinkedList;

public class LinkedListQueue<E> implements Queue<E> {
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
	public void enqueue(E e) {
		list.AddLast(e);
	}

	@Override
	public E first() {
		return list.first();
	}

	@Override
	public E dequeue() {
		return list.removeFirst();
	}

}
