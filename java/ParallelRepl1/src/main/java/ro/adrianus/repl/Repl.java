package ro.adrianus.repl;

import ro.adrianus.task.Task;

import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Repl {
    private Scanner scanner;

    public Repl() {
        scanner = new Scanner(System.in);
    }

    public void loop() {
        boolean running = true;
        ExecutorService pool = Executors.newFixedThreadPool(4);
        Runnable task1 = null, task2 = null;
        while(running) {
            System.out.print(">> ");
            String line = scanner.nextLine();
            if ("exit".equals(line)) running = false;
            if ("view task 1".equals(line)) {
                ((Task) task1).printConsole();
            }
            if ("view task 2".equals(line)) {
                ((Task) task2).printConsole();
            }
            if ("start task 1".equals(line)) {
                task1 = new Task();
                pool.execute(task1);
            }
            if ("start task 2".equals(line)) {
                task2 = new Task();
                pool.execute(task2);
            }
        }
        pool.shutdownNow();
    }
}
