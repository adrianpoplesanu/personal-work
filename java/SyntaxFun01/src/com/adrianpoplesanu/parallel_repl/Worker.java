package com.adrianpoplesanu.parallel_repl;

public class Worker implements Runnable {
    private String text;

    public Worker(String text) {
        this.text = text;
    }

    @Override
    public void run() {
        while(true) {
            System.out.print("\r" + text);
        }
    }
}
