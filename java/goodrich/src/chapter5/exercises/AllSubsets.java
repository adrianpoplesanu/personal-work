package chapter5.exercises;

public class AllSubsets {

	public static void printElements(int[] elements, int[] a) {
		for (int i = 0; i < elements.length; i++) {
			if (a[i] == 1) System.out.print(elements[i] + " ");
		}
		System.out.println("");
	}
	
	public static void back(int[] elements, int[] a, int k) {
		if (k == elements.length - 1) {
			printElements(elements, a);
		} else {
			a[k] = 0;
			while(a[k] < 2) {
				back(elements, a, k+1);
				a[k]++;
			}
		}
	}
	
	public static void main(String[] args) {
		int[] elements = { 1, 2, 3, 4 };
		int[] a = new int[elements.length];
		back(elements, a, 0);
	}
}
