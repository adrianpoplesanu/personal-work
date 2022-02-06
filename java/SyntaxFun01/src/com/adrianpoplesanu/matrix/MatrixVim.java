package com.adrianpoplesanu.matrix;

import java.util.Random;

public class MatrixVim {
    public static void main(String[] args) throws InterruptedException {
        String text = "adrianus";
        boolean[] show = new boolean[10];
        int[] count = new int[10];
        Random random = new Random();
        for (int i = 0; i < 10; i++) {
            count[i] = 0;
            show[i] = false;
        }
        int k = 0, maxChanges = 2;
        while(true) {
            for (int i = 0; i < 10; i++) {
                if (show[i]) {
                    if (k >= text.length()) k = 0;
                    System.out.print(text.charAt(k++) + " ");
                } else {
                    System.out.print("  ");
                }
                count[i]++;
            }
            System.out.println();
            Thread.sleep(100);
            for (int j = 0; j < maxChanges; j++) {
                int val = random.nextInt(10);
                if (count[val] > 6) {
                    show[val] = !show[val];
                    count[val] = 0;
                }
            }
        }
    }
}
