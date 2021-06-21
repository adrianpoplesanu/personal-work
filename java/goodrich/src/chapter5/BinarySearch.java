package chapter5;

public class BinarySearch {
	public static boolean binarySearch(int[] data, int target, int low, int high) {
		if (low > high) return false;
		int mid = (low + high) / 2;
		if (target == data[mid]) return true;
		if (target < data[mid]) return binarySearch(data, target, low, mid - 1);
		else return binarySearch(data, target, mid + 1, high);
	}

	public static void main(String[] args) {
		//System.out.println("binary search...");
		int a[] = {1, 2, 3, 5, 6, 8, 9};
		System.out.println(BinarySearch.binarySearch(a, 2, 0, 6));
		System.out.println(BinarySearch.binarySearch(a, 4, 0, 6));
		System.out.println(BinarySearch.binarySearch(a, 1, 0, 6));
		System.out.println(BinarySearch.binarySearch(a, 7, 0, 6));
		System.out.println(BinarySearch.binarySearch(a, 9, 0, 6));
	}
}
