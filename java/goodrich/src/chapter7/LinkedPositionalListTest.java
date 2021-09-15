package chapter7;

public class LinkedPositionalListTest {

	public static void main(String[] args) {
		PositionalList<String> names = new LinkedPositionalList<String>();
		names.addFirst("bebe dex");
		names.addBefore(names.first(), "ramunic");
		Position<String> cursor = names.first();
		while(cursor != null) {
			System.out.println(cursor.getElement());
			cursor = names.after(cursor);
		}
	}
}
