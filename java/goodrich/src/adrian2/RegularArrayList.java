package adrian2;

import java.util.Iterator;

public class RegularArrayList<E> implements List<E>, Iterable<E> {

	@Override
	public int size() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void add(int i, E e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public E get(int i) {
		// TODO Auto-generated method stub
		return null;
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

	class RegularArrayListIterator implements Iterator<E> {

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
		// TODO Auto-generated method stub
		return new RegularArrayListIterator();
	}
}
