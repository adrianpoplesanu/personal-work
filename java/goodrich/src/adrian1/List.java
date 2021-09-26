package adrian1;

public interface List<E> {
	int size();
	boolean isEmpty();
	
	void append(E e);
	void add(int i, E e);
	E get(int i);
	void set(int i, E e);
	E remove(int i);
}
