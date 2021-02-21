package worker;

public class Main {

	public void solve(int a[], int numThreads) {
		Thread[] t = new Thread[numThreads];
		int[] results = new int[numThreads];
		for (int i = 0; i < numThreads; i++) {
			t[i] = new Task(i, a);
			t[i].start();
		}
		
		for (int i = 0; i < numThreads; i++) {
			try {
				t[i].join();
				System.out.println("Thread " + ((Task)t[i]).getTaskId() + " has finished");
				results[i] = ((Task)t[i]).getResult();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		for (int i = 0; i < numThreads; i++) {
			System.out.println(results[i]);
		}
	}
	
	public static void main(String[] args) {
		int a[] = {67, 45, 32, 87, 34, 12, 6, 3, -5, 67, 4, 78, 89, 2};
		int numThreads = 2;
		Main main = new Main();
		main.solve(a, numThreads);
	}
}
