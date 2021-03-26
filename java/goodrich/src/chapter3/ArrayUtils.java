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
	}
}
