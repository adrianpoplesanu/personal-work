package chapter6;

public class ArrayStack<E> implements Stack<E> {
	public static final int capacity = 100;
	private E[] data;
	private int idx = -1;
	
	public ArrayStack() {
		this(capacity);
	}
	
	public ArrayStack(int capacity) {
		data = (E[]) new Object[capacity];
	}

	@Override
	public int size() {
		return idx + 1;
	}

	@Override
	public boolean isEmpty() {
		return idx == -1;
	}

	@Override
	public void push(E e) throws IllegalStateException {
		if (size() == data.length) throw new IllegalStateException("Stack is full");
		data[++idx] = e;
	}

	@Override
	public E top() {
		if (isEmpty()) return null;
		return data[idx];
	}

	@Override
	public E pop() {
		if (isEmpty()) return null;
		E result = data[idx];
		data[idx] = null; // this helps the garbage collector, the element is no longer referenced
		                  // leading to the element that data[idx] points to, to be freed
		idx--;
		return result;
	}
}
