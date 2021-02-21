package worker;

public class Task extends Thread {
	private int id;
	private int result;
	private int[] a;
	
	public Task(int id, int[] a) {
		this.id = id;
		this.a = a;
	}
	
	public String getTaskId() {
		return String.valueOf(this.id);
	}
	
	public int getResult() {
		return result;
	}

	@Override
	public void run() {
		System.out.println("running thread " + String.valueOf(this.id));
		Solver solver = new Solver();
		result = solver.findMinimum(a);
	}
}
