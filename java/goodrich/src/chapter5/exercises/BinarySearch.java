package chapter5.exercises;

public class BinarySearch {

	public static int binarySearch(int[] a, int target, int low, int high) {
		if (low > high) {
			return -1;
		} else {
			int mid = (low + high) / 2;
			if (target == a[mid]) return mid;
			else if (target < a[mid]) {
				return binarySearch(a, target, low, mid - 1);
			} else {
				return binarySearch(a, target, mid + 1, high);
			}
		}
	}
	
	public static void main(String[] args) {
		int[] a = {0, 2, 4, 5, 6, 7, 9};
		System.out.println(binarySearch(a, 5, 0, a.length - 1));
	}
}
