package chapter5;

public class RecursiveArraySumator2 {

	private static int recursiveSum(int a[], int low, int high) {
		if (low > high) return 0;
		if (low == high) return a[low];
		int mid = (low + high) / 2;
		return recursiveSum(a, low, mid) + recursiveSum(a, mid + 1, high);
	}
	
	public static void main(String[] args) {
		int a[] = { 4, 3, 2, 5, 6, 8 };
		System.out.println(recursiveSum(a, 0, 5));
	}
}
