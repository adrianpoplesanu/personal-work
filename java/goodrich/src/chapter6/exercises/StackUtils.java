package chapter6.exercises;

import chapter6.ArrayStack;
import chapter6.Stack;

public class StackUtils {
	
	public static <E> void transfer(Stack<E> S, Stack<E> T) {
		
	}

	public static <E> void emptyStack(Stack<E> stack) {
		// R-6.5
		if (!stack.isEmpty()) {
			stack.pop();
			emptyStack(stack);
		}
	}
	
	public static void main(String[] args) {
		ArrayStack<String> names = new ArrayStack<String>();
		names.push("dexiciul");
		names.push("ramunitz");
		names.push("adrianus");
		System.out.println(names.size());
		emptyStack(names);
		System.out.println(names.size());
	}
}
