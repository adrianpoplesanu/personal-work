package com.adrianpoplesanu.lambdas2;

public class TestingLambda {
    public static void main(String[] args) {
        System.out.println(print((a, b, c) -> a + b + c));
    }

    public static String print(Operations operations) {
        return operations.process("bebe dex", "12", "scump");
    }
}
