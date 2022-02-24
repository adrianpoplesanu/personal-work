package com.adrianpoplesanu.parallel_repl;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ParallelRepl {

    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(10);
        Worker worker1 = new Worker("aaa");
        Worker worker2 = new Worker("bbb");
        executor.execute(worker1);
        executor.execute(worker2);
    }
}
