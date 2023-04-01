package com.adrianpoplesanu.threading;

public class ThreadingTest4 {

    public void testingThreads() throws InterruptedException {
        Thread thread1 = new Thread(new Worker());
        Thread thread2 = new Thread(new Worker());
        Thread thread3 = new Thread(new Worker());

        thread1.start();
        thread2.start();
        thread3.start();

        thread1.join();
        thread2.join();
        thread3.join();

        System.out.println("after threads");
    }

    private class Worker implements Runnable {

        @Override
        public void run() {
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

    public static void main(String[] args) throws InterruptedException {
        ThreadingTest4 threadingTest4 = new ThreadingTest4();
        threadingTest4.testingThreads();
    }
}
