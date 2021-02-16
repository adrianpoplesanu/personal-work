package chapter1.exercises;

public class OddChecker {
	public boolean isOdd(int i) {
		while(i >= 2) i-= 2;
		if (i == 1) return false;
		return true;
	}

	public static void main(String[] args) {
		OddChecker oddChecker = new OddChecker();
		System.out.println(oddChecker.isOdd(56));
		System.out.println(oddChecker.isOdd(57));
		System.out.println(oddChecker.isOdd(1));
		System.out.println(oddChecker.isOdd(4));
		System.out.println(oddChecker.isOdd(0));
	}
}
