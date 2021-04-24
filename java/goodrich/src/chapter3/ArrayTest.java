package chapter3;

import java.util.Arrays;
import java.util.Random;

public class ArrayTest {

	public static void main(String[] args) {
		int data[] = new int[10];
		Random rand = new Random();
		rand.setSeed(System.currentTimeMillis());
		for (int i = 0; i < data.length; i++) {
			data[i] = rand.nextInt(100);
		}
		int orig[] = Arrays.copyOf(data, data.length);
		System.out.println("arrays are equal before sort: " + Arrays.equals(orig, data));
		Arrays.sort(data);
		System.out.println("arrays are equal after sort: " + Arrays.equals(orig, data));
		System.out.println("orig array: " + Arrays.toString(orig));
		System.out.println("sorted array: " + Arrays.toString(data));
	}
}
