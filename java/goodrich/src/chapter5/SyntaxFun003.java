package chapter5;

public class SyntaxFun003 {
	public static class A {
		private int a;
		protected int b;
		public int c;
	}
	
	public static class B extends A {
		B(int b, int c) {
			this.b = b;
			this.c = c;
		}
		
		void test() {
			//System.out.println(a); // a is not visible, it's private
			System.out.println(b);
			System.out.println(c);
		}
	}

	public static void main(String[] args) {
		B b = new B(2, 3);
		b.test();
	}
}
