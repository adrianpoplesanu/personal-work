package ro.adrianus.task;

import ro.adrianus.console.WorkerConsole;

public class Task implements Runnable {
    private WorkerConsole console;

    public Task() {
        console = new WorkerConsole();
    }

    public void printConsole() {
        console.print();
    }

    public void run() {
        // https://www.geeksforgeeks.org/thread-pools-java/
        try {
            for (int i = 0; i < 100; i++) {
                console.addLine(String.valueOf(i));
                Thread.sleep(1000);
            }
        } catch (InterruptedException e) {
            //throw new RuntimeException(e);
            System.out.println("task received interrupt from main thread, killing it");
        }
    }
}
