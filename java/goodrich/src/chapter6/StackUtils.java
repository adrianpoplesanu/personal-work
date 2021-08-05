package chapter6;

import java.util.Arrays;

public class StackUtils {
	
	public static <E> void reverse(E[] a) {
		Stack<E> stack = new ArrayStack<E>(a.length);
		for (int i = 0; i < a.length; i++) {
			stack.push(a[i]);
		}
		for (int i = 0; i < a.length; i++) {
			a[i] = stack.pop();
		}
	}
	
	public static void reverse(int[] a) {
		Stack<Integer> stack = new ArrayStack<Integer>(a.length);
		for (int i = 0; i < a.length; i++) {
			stack.push(a[i]);
		}
		for (int i = 0; i < a.length; i++) {
			a[i] = stack.pop();
		}		
	}

	public static void main(String[] args) {
		String[] words = { "adrianus", "ramunitz", "dexiciul" };
		reverse(words);
		System.out.println(Arrays.toString(words));
		
		int[] a = { 4, 5, 2 };
		reverse(a);
		System.out.println(Arrays.toString(a));
	}
}
