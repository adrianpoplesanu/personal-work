package chapter3;

import java.util.ArrayList;

public class SyntaxFun001 {

	public static void main(String[] args) {
		int []a; // this does not work in c
		int b[]; // this does work in c, it's the same as int *b; :))
		a = new int[3];
		b = new int[3];
		for (int i = 0; i < a.length; i++) a[i] = i;
		for (int i = 0; i < b.length; i++) b[i] = i * i;
		for (int i = 0; i < a.length; i++) System.out.println(a[i]);
		for (int i = 0; i < b.length; i++) System.out.println(b[i]);
		ArrayList<String> words = new ArrayList<String>();
	}
}
