package chapter7;

public class ArrayList<E> implements List<E> {
	private E[] data;
	public static final int capacity = 4;
	private int size = 0;

	public ArrayList() {
		this(capacity);
	}
	
	@SuppressWarnings("unchecked")
	public ArrayList(int capacity) {
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
	public E get(int i) throws IndexOutOfBoundsException {
		if (i < 0 || i >= size) throw new IndexOutOfBoundsException("Index " + i + " is out of bounds.");
		return data[i];
	}

	@Override
	public E set(int i, E e) throws IndexOutOfBoundsException {
		if (i < 0 || i >= size) throw new IndexOutOfBoundsException("Index " + i + " is out of bounds.");
		E old = data[i];
		data[i] = e;
		return old;
	}

	@Override
	public void add(int i, E e) throws IndexOutOfBoundsException {
		if (i < 0 || i >= size + 1) throw new IndexOutOfBoundsException("Index " + i + " is out of bounds.");
		if (size == capacity) throw new IndexOutOfBoundsException("List is full.");
		for (int j = size - 1; j > i; j--) data[j] = data[j - 1];
		data[i] = e;
		size++;
	}

	@Override
	public E remove(int i) throws IndexOutOfBoundsException {
		if (i < 0 || i >= size) throw new IndexOutOfBoundsException("Index " + i + " is out of bounds.");
		E res = data[i];
		for (int j = i; j < size - 1; j++) data[j] = data[j + 1];
		size--;
		return res;
	}
}
