package com.adrianpoplesanu.increment_test;

public class IncrementTest01 {
    public static void main(String[] args) {
        int i = 0;
        while (i++ < 10) {
            System.out.println(i);
        }

        for (int j = 0; j < 10; j++) {
            System.out.println(j);
        }
    }
}
