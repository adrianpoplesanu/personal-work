package chapter2.exercises;

public class OverflowClass {
	public void forceOverflow() {
		int a[] = new int[10];
		a[21] = 4;
	}
	
	public void getValue() throws Exception {
		try {
			forceOverflow();
		} catch(IndexOutOfBoundsException exception) {
			throw new Exception("bla bla bla");
		}
	}
	
	public static void main(String[] args) throws Exception {
		OverflowClass oc = new OverflowClass();
		oc.getValue();
	}
}
