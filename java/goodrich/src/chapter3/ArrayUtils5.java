package chapter3;

import java.lang.reflect.Array;

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
	
	public static void fill(int[] a, int val) {
		for (int i = 0; i < a.length; i++) {
			a[i] = val;
		}
	}
	
	@SuppressWarnings("unchecked")
	public static <T> T[] copyOf(T[] a, int n) {
		//T b[] = (T[]) new Object[n];
		T b[] = (T[]) Array.newInstance(a.getClass().getComponentType(), n);
		for (int i = 0; i < n; i++) {
			if (i < a.length) b[i] = a[i];
			else b[i] = null;
		}
		return b;
	}
	
    @SuppressWarnings("unchecked")
    public static <T> T[] copyOf2(T[] original, int newLength) {
        return (T[]) copyOf2(original, newLength, original.getClass());
    }
	
    @SuppressWarnings("unchecked")
	public static <T,U> T[] copyOf2(U[] original, int newLength, Class<? extends T[]> newType) {
        T[] copy = ((Object)newType == (Object)Object[].class)
            ? (T[]) new Object[newLength]
            : (T[]) Array.newInstance(newType.getComponentType(), newLength);
        if (newLength > original.length) {
        	for(int i = 0; i < original.length; i++) copy[i] = (T) original[i];
        } else {
        	for(int i = 0; i < newLength; i++) copy[i] = (T) original[i];
        }
        return copy;
    }
	
	public static int[] copyOf(int[] a, int n) {
		// TODO: implement it
		return null;
	}
	
	public static void main(String args[]) {
		String a[] = new String[5];
		ArrayUtils5.fill(a, "aaa");
		for (int i = 0; i < a.length; i++) System.out.println(a[i]);
		boolean b[] = new boolean[5];
		ArrayUtils5.fill(b, true);
		for (int i = 0; i < b.length; i++) System.out.println(b[i]);
		String c[] = new String[10]; // this is so stupid java, java!
		c = ArrayUtils5.copyOf(a, 10);
		for (int i = 0; i < c.length; i++) System.out.println(c[i]);
		Os os[] = new Os[5];
		Os base = new Os();
		base.setName("lin");
		ArrayUtils5.fill(os, base);
		for (int i = 0; i < os.length; i++) System.out.println(os[i].getName());
		Os os2[]; // this is so stupid, java!
		//System.out.println(ArrayUtils5.copyOf(os, 10).getClass().toString());
		os2 = ArrayUtils5.copyOf2(os, 10);
		System.out.println(os2.length);
		for (int i = 0; i < os2.length; i++) {
			System.out.println(os2[i]);
		}
	}
}
