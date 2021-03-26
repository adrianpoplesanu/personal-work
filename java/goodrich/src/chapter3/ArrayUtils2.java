package chapter3;

public class ArrayUtils2 {
	public static void change(Os os) {
		os.name = "lin";
	}
	
	public static void main(String args[]) {
		Os os = new Os();
		os.name = "win";
		System.out.println(os.name);
		change(os);
		System.out.println(os.name);
	}
}
