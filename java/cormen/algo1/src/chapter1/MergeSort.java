package chapter1;

public class MergeSort {
	public static void sort(int a[], int low, int high) {
		if (low < high) {
			int mid = (low + high) / 2;
			sort(a, low, mid);
			sort(a, mid + 1, high);
			merge(a, low, mid, high);
		}
	}
	
	public static void merge(int a[], int low, int mid, int high) {
		int b[] = new int[a.length];
		int i = low, j = mid + 1, k = low;
		while(i <= mid && j <= high) {
			if (a[i] < a[j]) b[k++] = a[i++];
			else b[k++] = a[j++];
		}
		while(i <= mid) b[k++] = a[i++];
		while(j <= high) b[k++] = a[j++];
		for (k = low; k <= high; k++) a[k] = b[k];
	}
	
	public static void print(int a[]) {
		for (int e : a) {
			System.out.print(e + " ");
		}
		System.out.println("");
	}

	public static void main(String[] args) {
		int a[] = {3, 8, 2, 6, 7, 1, 4, 9, 5};
		sort(a, 0, a.length - 1);
		print(a);
	}
}
