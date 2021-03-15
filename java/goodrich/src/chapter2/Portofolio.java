package chapter2;

public class Portofolio<T> {
	T[] data;
	
	@SuppressWarnings("unchecked")
	Portofolio(int capacity) {
		data = (T[]) new Object[capacity];
	}
	
	public T GetAt(int index) {
		return data[index];
	}
	
	public void SetAt(T element, int index) {
		data[index] = element;
	}
	
	public static void main(String[] args) {
		Portofolio<String> p = new Portofolio<String>(10);
		p.SetAt("teeest", 7);
		System.out.println(p.GetAt(7));
	}
}
