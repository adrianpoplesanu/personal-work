package chapter7;

public class DynamicArrayList<E> extends ArrayList<E> {

	@SuppressWarnings("unchecked")
	protected void resize(int capacity) {
    	E[] temp = (E[]) new Object[capacity];
    	for (int i = 0; i < size; i++) temp[i] = data[i];
    	data = temp;
    }

    @Override
    public void add(int i, E e) throws IndexOutOfBoundsException {
    	if (i < 0 || i >= size + 1) throw new IndexOutOfBoundsException("Index " + i + " is out of bounds.");
    	if (size == capacity) {
    		resize(2 * capacity);
    		capacity = 2 * capacity;
    	}
    	super.add(i, e);
    }
}
