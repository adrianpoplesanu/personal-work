package chapter1.exercises;

public class MultiplierTest {
	
	public boolean isMultiple(long n, long m) {
		return (double)n / m == (double)(n / m);
	}

	public static void main(String[] args) {
		MultiplierTest multiplierTest = new MultiplierTest();
		System.out.println(multiplierTest.isMultiple(60, 10));
	}
}
