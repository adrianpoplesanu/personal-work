package chapter3;

public class ArrayUtils5 {
	public static <T> void fill(T[] a, T val) {
		for (int i = 0; i < a.length; i++) {
			a[i] = val;
		}
	}
	
	public static void fill(boolean[] a, boolean val) {
		for (int i = 0; i < a.length; i++) {
			a[i] = val;
		}
	}
	
	public static <T> void copyOf(T[] a, int n) {
		//...
	}
	
	public static void copyOf(int[] a, int n) {
		//...
	}
	
	public static void main(String args[]) {
		String a[] = new String[5];
		ArrayUtils5.fill(a, "aaa");
		for (int i = 0; i < a.length; i++) System.out.println(a[i]);
		boolean b[] = new boolean[5];
		ArrayUtils5.fill(b, true);
		for (int i = 0; i < b.length; i++) System.out.println(b[i]);
	}
}
