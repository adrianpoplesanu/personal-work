package com.adrianpoplesanu.threading;

public class ThreadingTest1 {

    public void execute() {
        System.out.println("initializaing threads");
        for (int i = 0; i < 5; i++) {
            Worker worker = new Worker(i);
            Thread thread = new Thread(worker);
            thread.start();
        }
        System.out.println("threads initialized!");
    }

    public static void main(String[] args) {
        ThreadingTest1 threadingTest = new ThreadingTest1();
        threadingTest.execute();
    }

    private class Worker implements Runnable {

        private int id;

        public Worker(int id) {
            this.id = id;
        }

        @Override
        public void run() {
            int i = 0;
            System.out.println("starting " + id);
            while (i < 100) {
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                i++;
            }
            System.out.println("finishing " + id);
        }
    }
}
