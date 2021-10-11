package adrian1;

public class LinkedListPositionalTest {

	public static void main(String[] args) {
		LinkedListPositional<String> words = new LinkedListPositional<String>();
		words.addFirst("buna");
		words.addLast("dimineata");
		words.addLast("bebe");
		words.addLast("dex");
		System.out.println(words.get(3));
		
		words.add(0, "aaa");
		words.add(words.size(), "bbb");
		
		Position<String> cursor = words.first();
		while(cursor != null) {
			System.out.println(cursor.getElement());
			cursor = words.after(cursor);
		}
	}
}
