package worker;

import java.util.Arrays;

public class Main {

	public void solve(int a[], int numThreads) {
		Thread[] t = new Thread[numThreads];
		int[] results = new int[numThreads];
		int[] input;
		for (int i = 0; i < numThreads; i++) {
			if (i == 0) input = Arrays.copyOfRange(a, 0, a.length / 2);
			else input = Arrays.copyOfRange(a, a.length / 2, a.length);
			t[i] = new Task(i, input);
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
