package chapter3;

public class ArrayList2<E> {
	private E elem[];
	private int capacity;
	private int size;

	public ArrayList2() {
		capacity = 4;
		size = 0;
		elem = (E[]) new Object[capacity];
	}

	public void add(E e) {
		elem[size++] = e;
	}

	public E pop() {
		if (size > 0) {
			E ret = elem[size - 1];
			size--;
			return ret;
		} else {
			return null;
		}
	}
}
