package chapter5;

public class RecursiveArraySumator {

	private static int calculateSum(int a[], int pos) {
		if (pos == 0) return a[0];
		return a[pos] + calculateSum(a, pos - 1);
	}
	
	public static void main(String[] args) {
		int a[] = { 4, 3, 2, 6, 5, 8};
		System.out.println(calculateSum(a, 0));
		System.out.println(calculateSum(a, 1));
		System.out.println(calculateSum(a, 2));
        System.out.println(calculateSum(a, 3));
        System.out.println(calculateSum(a, 4));
        System.out.println(calculateSum(a, 5));
	}

}
