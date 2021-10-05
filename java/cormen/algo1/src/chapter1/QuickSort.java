package chapter1;

public class QuickSort {
	
	private static void swap(int[] a, int i, int j) {
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
	
	private static int partition(int[] a, int low, int high) {
		int i = low - 1;
		int pivot = a[high];
		for (int j = low; j <= high; j++) {
			if (a[j] < pivot) {
				i++;
				swap(a, i, j);
			}
		}
		swap(a, i + 1, high);
		return i + 1;
	}
	
	public static void quickSort(int[] a, int low, int high) {
		if (low < high) {
			int pos = partition(a, low, high);
			quickSort(a, low, pos - 1);
			quickSort(a, pos + 1, high);
		}
	}

	public static void main(String[] args) {
		int a[] = {6, 2, 8, 3, 5, 4, 1, 9, 7};
		quickSort(a, 0, a.length - 1);
		SimpleArrayUtils.printSimpleArray(a);
	}
}
