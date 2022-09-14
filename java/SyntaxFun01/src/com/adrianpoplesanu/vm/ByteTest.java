package com.adrianpoplesanu.vm;

public class ByteTest {
    public static void main(String[] args) {
        byte a = 0;
        int i = 0;
        while(i < 256) {
            i++;
            System.out.println(a++);
        }
    }
}
