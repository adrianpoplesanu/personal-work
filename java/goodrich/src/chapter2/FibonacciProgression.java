package chapter2;

public class FibonacciProgression extends Progression {
	protected long prev;
	
	public FibonacciProgression() {
		this (0, 1);
	}
	
	public FibonacciProgression(long first, long second) {
		super(first);
		prev = second - first;
	}
	
	protected void advance() {
		long temp = prev;
		prev = current;
		current = prev + temp;
	}
	
	public static void main(String[] args) {
		FibonacciProgression fp = new FibonacciProgression();
		for (int i = 0; i < 6; i++) System.out.println(fp.nextValue());
	}
}
