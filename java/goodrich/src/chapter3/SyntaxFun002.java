package chapter3;

import java.util.ArrayList;

public class SyntaxFun002 {
	
	public static void main(String[] args) {
		//ArrayList2<String> words = new ArrayList2<String>();
		SinglyLinkedList<String> words = new SinglyLinkedList<String>();
		words.AddLast("hello");
		System.out.println(words);
		
		ArrayList<String> names = new ArrayList<String>();
		names.add("dexiciul");
		System.out.println(names);
	}
}
