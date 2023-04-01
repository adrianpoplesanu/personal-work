package com.adrianpoplesanu.threading;

public class ThreadingTest3 {

    public void testThreads() {
        for (int i = 0; i < 5; i++) {
            Worker worker = new Worker(i);
            Thread thread = new Thread(worker);
            thread.start();
        }
        System.out.println("after threads");
    }

    private class Worker implements Runnable {

        private int id;

        public Worker(int id) {
            this.id = id;
        }

        @Override
        public void run() {
            System.out.println("running thread " + id);

            for (int i = 0; i < 100; i++) {
                System.out.println(i);
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    public static void main(String[] args) {
        ThreadingTest3 threadingTest3 = new ThreadingTest3();
        threadingTest3.testThreads();
        System.out.println("resuming execution");
    }
}
