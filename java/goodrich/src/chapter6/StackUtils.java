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

	public static boolean isMatched(String expression) {
		final String opening = "([{";
		final String closing = ")]}";
		Stack<Character> stack = new LinkedListStack<Character>();
		for (char c : expression.toCharArray()) {
			if (opening.indexOf(c) != -1) {
				stack.push(c);
			} else {
				if (closing.indexOf(c) != -1) {
					if (stack.isEmpty()) return false;
					if (closing.indexOf(c) != opening.indexOf(stack.pop())) return false;
				}
			}
		}
		return stack.isEmpty();
	}

	public static boolean isHTMLValid(String html) {
		Stack<String> buffer = new LinkedListStack<String>();
		int j = html.indexOf('<');
		while (j != -1) {
			int k = html.indexOf('>', j + 1);
			if (k == -1) return false;
			String tag = html.substring(j + 1, k);
			if (tag.startsWith("/")) {
				if (buffer.isEmpty()) return false;
				else {
					if (!tag.substring(1).equals(buffer.pop())) return false;
				}
			} else {
				buffer.push(tag);
			}
			j = html.indexOf('<', k + 1);
		}
		return buffer.isEmpty();
	}

	public static void main(String[] args) {
		String[] words = { "adrianus", "ramunitz", "dexiciul" };
		reverse(words);
		System.out.println(Arrays.toString(words));
		
		int[] a = { 4, 5, 2, 6 };
		reverse(a);
		System.out.println(Arrays.toString(a));

		Integer[] numbers = { 5, 7, 6, 2 };
		reverse(numbers);
		System.out.println(Arrays.toString(numbers));

		System.out.println(isMatched("( )(( )){([( )])}"));
		System.out.println(isMatched("((( )(( )){([( )])}))"));
		System.out.println(isMatched(")(()){([()])}"));
		System.out.println(isMatched("({[])}"));
		System.out.println(isMatched(" ("));
		System.out.println(isMatched(" )"));

		System.out.println(isHTMLValid("<html><head></head><body></body></html>"));
		System.out.println(isHTMLValid("<html><head></head><body></html>"));
		System.out.println(isHTMLValid("<html><head><body></head></body></html>"));
		System.out.println(isHTMLValid("<html><head></head></body></html>"));
	}
}
