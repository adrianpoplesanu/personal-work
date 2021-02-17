package chapter1.exercises;

public class SumCalculator {

	public int sum(int n) {
		int total = 0;
		for (int i = 0; i <= n; ++i) total += i;
		return total;
	}
	
	public int evenSum(int n) {
		int total = 0;
		for (int i = 0; i <= n; ++i) if (i % 2 == 0) total += i;
		return total;
	}
	
	public int squareSum(int n) {
		int total = 0;
		for (int i = 0; i <= n; ++i) total += i * i;
		return total;
	}
	
	public static void main(String[] args) {
		SumCalculator sumCalculator = new SumCalculator();
		System.out.println(sumCalculator.sum(5));
		System.out.println(sumCalculator.sum(12));
		System.out.println(sumCalculator.sum(45));
		System.out.println(sumCalculator.evenSum(5));
		System.out.println(sumCalculator.evenSum(12));
		System.out.println(sumCalculator.evenSum(45));
		System.out.println(sumCalculator.squareSum(5));
		System.out.println(sumCalculator.squareSum(12));
		System.out.println(sumCalculator.squareSum(45));
	}
}
