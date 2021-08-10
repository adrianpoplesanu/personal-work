package chapter6;

public class ArrayQueue<E> implements Queue<E> {
	private static final int capacity = 4;
	private E[] data;
	private int front = 0;
	private int size = 0;
	
	@SuppressWarnings("unchecked")
	public ArrayQueue() {
		data = (E[]) new Object[capacity];
	}
	
	@SuppressWarnings("unchecked")
	public ArrayQueue(int capacity) {
		data = (E[]) new Object[capacity];
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
	public void enqueue(E e) throws IllegalStateException {
		if (size == data.length) throw new IllegalStateException("Queue is full.");
		data[(front + size) % capacity] = e;
		size++;
	}

	@Override
	public E first() {
		if (isEmpty()) return null;
		return data[front];
	}

	@Override
	public E dequeue() {
		if (isEmpty()) return null;
		E res = data[front];
		front++;
		if (front >= capacity) front -= capacity;
		size--;
		return res;
	}
}
