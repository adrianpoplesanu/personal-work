package chapter6;

public class ArrayQueueTest {

	public static void main(String[] args) {
		Queue<String> queue = new ArrayQueue<String>();
		
		queue.enqueue("bebe");
		queue.enqueue("dex");
		queue.enqueue("e");
		queue.enqueue("scump");
		
		System.out.println(queue.dequeue());
		System.out.println(queue.dequeue());
		System.out.println(queue.dequeue());
		System.out.println(queue.dequeue());
		System.out.println(queue.dequeue());
		
		queue.enqueue("test");
		queue.enqueue("test");

		System.out.println(queue.dequeue());
		System.out.println(queue.dequeue());
		
		Queue<Integer> numbers = new ArrayQueue<Integer>();
		
		numbers.enqueue(1);
		numbers.enqueue(2);
		numbers.enqueue(3);
		numbers.enqueue(4);
		
		System.out.println(numbers.dequeue());
		System.out.println(numbers.dequeue());
		System.out.println(numbers.dequeue());
		System.out.println(numbers.dequeue());
		System.out.println(numbers.dequeue());
	}
}
