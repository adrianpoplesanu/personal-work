package chapter3;

import java.util.ArrayList;

public class ArrayTest2 {

	public static void main(String[] args) {
		ArrayList<String> names = new ArrayList<String>();
		names.add("adrianus");
		names.add("dexiciul");
		names.add("ramonice");
		System.out.println(names);
		
		ArrayList<Integer> score = new ArrayList<Integer>();
		score.add(5);
		int b = 7;
		score.add(b);
		System.out.println(score);
		
		SinglyLinkedList<String> names2 = new SinglyLinkedList<String>();
		names2.AddLast("adrianus");
		names2.AddLast("dexiciul");
		names2.AddLast("ramonice");
		System.out.println(names2);
		
		SinglyLinkedList<Integer> score2 = new SinglyLinkedList<Integer>();
		score2.AddLast(10);
		score2.AddLast(20);
		score2.AddLast(30);
		System.out.println(score2);
	}
}
