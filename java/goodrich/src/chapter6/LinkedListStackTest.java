package chapter6;

public class LinkedListStackTest {

	public static void main(String[] args) {
		LinkedListStack<Integer> stack = new LinkedListStack<Integer>();
		stack.push(5);
		stack.push(3);
		System.out.println(stack.top());
		System.out.println(stack.pop());
		System.out.println(stack.pop());
		System.out.println(stack.pop());
		
		LinkedListStack<String> dogs = new LinkedListStack<String>();
		dogs.push("dexiciul");
		dogs.push("bebe dex");
		System.out.println(dogs.top());
		System.out.println(dogs.pop());
		System.out.println(dogs.pop());
		System.out.println(dogs.pop());
	}
}
