package chapter3;

public class ArrayList2Test {

	public static void main(String[] args) {
		ArrayList2<String> a = new ArrayList2<String>();
		a.add("buna");
		a.add("dimineata");
		ArrayList2<Integer> b = new ArrayList2<Integer>();
		b.add(5);
		b.add(6);

		String last_string = a.pop();
		System.out.println(last_string);
		
		int last_int = b.pop();
		System.out.println(last_int);
	}
}
