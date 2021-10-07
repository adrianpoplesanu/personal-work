package chapter1;

public class BubbleSort {

	public static void bubbleSort(int[] a) {
		boolean sorted = false;
		while(!sorted) {
			sorted = true;
			for (int i = 0; i < a.length - 1; i++) {
				if (a[i] > a[i + 1]) {
					sorted = false;
					int temp = a[i];
					a[i] = a[i + 1];
					a[i + 1] = temp;
				}
			}
		}
	}
	
	public static void main(String[] args) {
		int[] a = {6, 3, 9, 2, 8, 1, 7, 5, 4};
		bubbleSort(a);
		SimpleArrayUtils.printSimpleArray(a);
	}

}
