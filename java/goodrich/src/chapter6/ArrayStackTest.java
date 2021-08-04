package chapter6;

public class ArrayStackTest {

	public static void main(String[] args) {
		ArrayStack<String> stack = new ArrayStack<String>();
		System.out.println(stack.isEmpty());
		System.out.println(stack.pop());
		System.out.println(stack.top());
		System.out.println(stack.size());
		stack.push("dexiciul");
		stack.push("ramunitz");
		stack.push("adrianus");
		System.out.println(stack.size());
		System.out.println(stack.top());
		System.out.println(stack.pop());
		System.out.println(stack.pop());
		System.out.println(stack.top());
		System.out.println(stack.pop());
		System.out.println(stack.size());
	}
}
