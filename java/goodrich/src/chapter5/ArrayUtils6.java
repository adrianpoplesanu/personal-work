package chapter5;

public class ArrayUtils6 {

	public static <T> void reverse(T a[]) {
		switch_over(a, 0, a.length - 1);
	}
	
	public static void reverse(int a[]) {
		switch_over(a, 0, a.length - 1);
	}
	
	private static <T> void switch_over(T a[], int low, int high) {
		if (low < high) {
			T temp = a[low];
			a[low] = a[high];
			a[high] = temp;
			switch_over(a, low + 1, high - 1);
		}
	}
	
	private static void switch_over(int a[], int low, int high) {
		if (low < high) {
			int temp = a[low];
			a[low] = a[high];
			a[high] = temp;
			switch_over(a, low + 1, high - 1);
		}
	}
	
	public static void display(int a[]) {
		System.out.print("[");
		for (int i = 0; i < a.length; i++) {
			if (i == 0) System.out.print(a[i]);
			else {
				System.out.print(", ");
				System.out.print(a[i]);
			}
		}
		System.out.println("]");
	}

	public static <T> void display(T a[]) {
		System.out.print("[");
		for (int i = 0; i < a.length; i++) {
			if (i == 0) System.out.print(a[i]);
			else {
				System.out.print(", ");
				System.out.print(a[i]);
			}
		}
		System.out.println("]");
	}
	
	public static void main(String[] args) {
		int a[] = { 2, 3, 4 };
		display(a);
		reverse(a);
		display(a);
		
		String words[] = { "like", "violence", "break", "the", "silence" };
		display(words);
		reverse(words);
		display(words);
	}
}
