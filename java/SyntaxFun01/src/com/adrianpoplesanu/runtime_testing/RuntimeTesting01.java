package com.adrianpoplesanu.runtime_testing;

import java.util.ArrayList;
import java.util.List;

public class RuntimeTesting01 {

    public void run() {
        List<Integer> a = new ArrayList<>();
        int i = 0;
        while (i < 100000) {
            a.add(i);
            i++;
        }
    }

    public static void main(String[] args) {
        RuntimeTesting01 runtimeTesting01 = new RuntimeTesting01();
        long start = System.nanoTime();
        runtimeTesting01.run();
        long end = System.nanoTime();
        long duration = (end - start) / 1000000;
        double timeInSeconds = (double)duration / 1000;
        System.out.println("ran for: " + timeInSeconds + "sec");
    }
}
