package chapter2;

public class ArrayUtils {
	public static <T> void reverse(T[] objects) {
		int size = objects.length;
		int i = 0, j = size - 1;
		while (i < j) {
			T temp = objects[i];
			objects[i++] = objects[j];
			objects[j--] = temp;
		}
	}
	
	public static void main(String args[]) {
		String a[] = {"aaa", "bbb", "ccc", "ddd", "eee"};
		ArrayUtils.reverse(a); // this does not work for ints
		for (int i = 0; i < a.length; i++) System.out.println(a[i]);
	}
}