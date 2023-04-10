package com.adrianpoplesanu.threading;

public class ThreadingTest5 {

    int contor = 0;

    public void testingThreads() throws InterruptedException {
        Thread thread1 = new Thread(new Worker());
        Thread thread2 = new Thread(new Worker());

        thread1.start();
        thread1.join();

        thread2.start();
        thread2.join();

        System.out.println("after threads");
    }

    private class Worker implements Runnable {

        @Override
        public void run() {
            System.out.println("starting a thread");
            for (int i = 0; i < 100; i++) {
                contor++;
                System.out.println(i);
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
            System.out.println("finishing a thread");
        }
    }

    public static void main(String[] args) throws InterruptedException {
        ThreadingTest5 threadingTest5 = new ThreadingTest5();
        threadingTest5.testingThreads();

        System.out.println("contor: " + threadingTest5.contor);
    }
}
