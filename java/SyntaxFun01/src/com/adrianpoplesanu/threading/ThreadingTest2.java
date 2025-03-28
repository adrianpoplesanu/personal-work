package com.adrianpoplesanu.threading;

public class ThreadingTest2 {

    private int sharedValue = 0;

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
        ThreadingTest2 threadingTest = new ThreadingTest2();
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
                    if (id == 0) {
                        sharedValue = 5;
                    } else {
                        sharedValue++;
                    }
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                i++;
            }
            System.out.println("finishing " + id + " sharedValue=" + sharedValue);
        }
    }
}
