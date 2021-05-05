package chapter3;

public class InsertionSort {

	public static void main(String[] args) {
		char a[] = {'b', 'c', 'd', 'a', 'e', 'h', 'g', 'f'};
		for (int i = 1; i < a.length; i++) {
			int poz = i;
			char curent = a[i];
			while(poz > 0 && curent < a[poz - 1]) {
				a[poz] = a[poz - 1];
				poz--;
			}
			a[poz] = curent;
		}
		for (int i = 0; i < a.length; i++) System.out.print(a[i] + " ");
		System.out.println("");
	}
}
