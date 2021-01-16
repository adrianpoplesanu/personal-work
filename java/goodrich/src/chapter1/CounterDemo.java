package chapter1;

public class CounterDemo {

	public static void main(String[] args) {
		Counter c;
		c = new Counter();
		c.increment();
		c.increment(3);
		int temp = c.getCount();
		System.out.println(temp);
	}
}
