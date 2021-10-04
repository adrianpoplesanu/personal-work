package chapter1;

public class InsertionSort {

	public static void printSimpleArray(int arr[]) {
		for (int e : arr) {
			System.out.print(e + " ");
		}
		System.out.println("");
	}

	public static void insertionSort(int a[]) {
		for (int i = 1; i < a.length; i++) {
			int target = a[i];
			int poz = i - 1;
			while (poz >= 0 && a[poz] > target) {
				a[poz + 1] = a[poz];
				poz--;
			}
			a[poz + 1] = target;
		}
	}
	
	public static void main(String[] args) {
		int a[] = {5, 2, 8, 4, 7, 1, 6, 9, 3};
		insertionSort(a);
		printSimpleArray(a);
	}
}
