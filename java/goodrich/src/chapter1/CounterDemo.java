package chapter1;

public class CounterDemo {

	public static void main(String[] args) {
		Counter c;
		c = new Counter();
		c.increment();
		c.increment(3);
		int temp = c.getCount();
		System.out.println(temp); // 4
		c.reset();
		Counter d = new Counter(5);
		d.increment();
		Counter e = d;
		temp = e.getCount();
		System.out.println(temp); // 6
		e.increment();
		temp = d.getCount();
		System.out.println(temp);  // 7
		d.reset();
		temp = d.getCount();
		System.out.println(temp); // 0
	}
}
