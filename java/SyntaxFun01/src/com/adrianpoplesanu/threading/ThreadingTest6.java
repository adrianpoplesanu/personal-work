package com.adrianpoplesanu.threading;

public class ThreadingTest6 {

    private class Worker implements Runnable {

        private int a;

        public Worker(int a) {
            this.a = a;
        }

        @Override
        public void run() {
            System.out.println(a);
        }
    }

    public void runTest() {
        Thread th1 = new Thread(new Worker(5));
        Thread th2 = new Thread(new Worker(6));
        Thread th3 = new Thread(new Worker(7));

        th1.start();
        th2.start();
        th3.start();
    }

    public static void main(String[] args) {
        ThreadingTest6 threadingTest6 = new ThreadingTest6();
        threadingTest6.runTest();
    }
}
