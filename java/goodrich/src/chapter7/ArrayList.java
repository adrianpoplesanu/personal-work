package chapter7;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class ArrayList<E> implements List<E>, Iterable<E> {
	protected E[] data;
	public static int capacity = 4; // this can be final for fixed length, i inherit this in my dynamic implementation so it can't be final anymore
	protected int size = 0;

	public ArrayList() {
		this(capacity);
	}
	
	@SuppressWarnings("unchecked")
	public ArrayList(int capacity) {
		data = (E[]) new Object[capacity];
	}
	
	@Override
	public int getSize() {
		return size;
	}
	
	public int getCapacity() {
		return capacity;
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
		for (int j = size; j > i; j--) data[j] = data[j - 1];
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
	
	// iterators
	private class ArrayIterator implements Iterator<E> {
		private int j = 0;
		private boolean removable = false;

		@Override
		public boolean hasNext() {
			return j < size;
		}

		@Override
		public E next() throws NoSuchElementException {
			if (j == size) throw new NoSuchElementException("No next element.");
			removable = true;
			return data[j++];
		}
		
		public void remove() throws IllegalStateException {
			if (!removable) throw new IllegalStateException("Nothing to remove.");
			ArrayList.this.remove(j - 1);
			j--;
			removable = false;
		}
	}

	@Override
	public Iterator<E> iterator() {
		return new ArrayIterator();
	}
}
