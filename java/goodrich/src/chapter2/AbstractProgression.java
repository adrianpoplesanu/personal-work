package chapter2;

public abstract class AbstractProgression {
	protected long current;
	
	public AbstractProgression() {
		this(0);
	}
	
	public AbstractProgression(long start) {
		current = start;
	}
	
	public long nextValue() {
		long answer = current;
		advance();
		return answer;
	}
	
	protected abstract void advance();
	
	public void printProgression(int n) {
		for (int i = 0; i < n; i++) {
			System.out.println(" " + nextValue());
		}
		System.out.println();
	}
}
