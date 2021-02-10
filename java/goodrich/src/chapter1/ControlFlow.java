package chapter1;

public class ControlFlow {
	private static final void println(String[] names) {
		for (String name : names) {
			System.out.println(name);
		}
	}

	public static void main(String[] args) {
		String[] names = new String[5];
		names[0] = "aaa";
		names[1] = "bbb";
		names[2] = "ccc";
		names[3] = "ddd";
		names[4] = "eee";
		ControlFlow.println(names);
		for (String name : names) {
			name = name.toUpperCase();
			System.out.println(name);
		}
		for (int i = 0; i < names.length; i++) {
			names[i] = names[i] + "qqq";
		}
		for (int i = 0; i < names.length; i++) {
			System.out.println(names[i]);
		}
		for (String name : names) {
			System.out.println(name);
		}
	}

}
