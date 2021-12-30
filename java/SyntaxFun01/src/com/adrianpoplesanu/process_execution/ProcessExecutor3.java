package com.adrianpoplesanu.process_execution;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ProcessExecutor3 {
    private static class Worker implements Runnable {

        @Override
        public void run() {
            System.out.println("ran it!");
        }
    }

    public static void testWorker() {
        Worker worker = new Worker();
        //Executors.newSingleThreadExecutor().submit(worker);
        //System.out.println("process should terminate now");

        ExecutorService service = Executors.newSingleThreadExecutor();
        service.submit(worker);
        service.shutdown();
    }
}
