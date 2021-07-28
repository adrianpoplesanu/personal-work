package chapter5.exercises;

public class HarmonicNumbers {
	public static float harmonic(int n) {
		if (n == 1) {
			return 1;
		} else {
			return harmonic(n - 1) + 1 / (float)n;
		}
	}

	public static void main(String[] args) {
        System.out.println(harmonic(3));
	}
}
