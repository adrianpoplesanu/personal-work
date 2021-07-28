package chapter5;

public class FibonacciRecursive {
	public static long[] fibonacci(int n) {
		if (n <= 1) {
			long[] answer = {n, 0};
			return answer;
		} else {
			long[] temp = fibonacci(n - 1);
			long[] answer = {temp[0] + temp[1], temp[0]};
			return answer;
		}
	}

	public static void main(String[] args) {
		long[] result = fibonacci(8);
		System.out.println(result[0]);
	}
}
