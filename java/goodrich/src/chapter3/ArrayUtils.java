package chapter3;

public class ArrayUtils {
	public <T> void reverse(T a[]) {
		int i = 0, j = a.length - 1;
		while(i < j) {
			T temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
			j--;
		}
	}
	
	public void reverse(int a[]) {
		int i = 0, j = a.length - 1;
		while(i < j) {
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
			j--;
		}
	}

	public static void main(String args[]) {
		ArrayUtils au = new ArrayUtils();
		Os os[] = new Os[3];
		os[0] = new Os();
		os[1] = new Os();
		os[2] = new Os();
		os[0].setName("lin");
		os[1].setName("mac");
		os[2].setName("win");
		au.reverse(os);
		for (int i = 0; i < os.length; i++) {
			System.out.println(os[i].getName());
		}
		
		int a[] = new int[3];
		a[0] = 3;
		a[1] = 2;
		a[2] = 1;
		au.reverse(a);
		for (int i = 0; i < a.length; i++) {
			System.out.println(a[i]);
		}
	}
}
