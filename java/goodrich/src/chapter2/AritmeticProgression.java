package chapter2;

public class AritmeticProgression extends Progression {
	protected long increment;

	public AritmeticProgression() {
		this(1, 0);
	}
	
	public AritmeticProgression(long stepsize) {
		this(stepsize, 0);
	}
	
	public AritmeticProgression(long stepsize, long start) {
		super(start);
		increment = stepsize;
	}
	
	protected void advance() {
		current += increment;
	}
}
