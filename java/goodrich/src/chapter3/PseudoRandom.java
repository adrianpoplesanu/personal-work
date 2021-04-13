package chapter3;

import java.util.Random;

public class PseudoRandom {

	public static void main(String[] args) {
		Random random = new Random();
		int a = random.nextInt();
		System.out.println(a);
		
		random.setSeed(12); // always same seed, so same number
		a = random.nextInt();
		System.out.println(a);
	}
}
