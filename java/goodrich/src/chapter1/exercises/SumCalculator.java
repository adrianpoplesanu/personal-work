package chapter1.exercises;

public class SumCalculator {

	public int sum(int n) {
		int total = 0;
		for (int i = 0; i <= n; ++i) total += i;
		return total;
	}
	
	public static void main(String[] args) {
		SumCalculator sumCalculator = new SumCalculator();
		System.out.println(sumCalculator.sum(5));
		System.out.println(sumCalculator.sum(12));
		System.out.println(sumCalculator.sum(45));
	}
}
