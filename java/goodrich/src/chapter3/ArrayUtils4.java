package chapter3;

import java.util.Arrays;

public class ArrayUtils4 {

	public static void main(String[] args) {
		int a[] = new int[5];
		Arrays.fill(a, 22);
		for (int i = 0; i < a.length; i++) System.out.println(a[i]);
	}
}
