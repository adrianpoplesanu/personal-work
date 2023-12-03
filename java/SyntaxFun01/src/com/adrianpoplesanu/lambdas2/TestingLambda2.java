package com.adrianpoplesanu.lambdas2;

public class TestingLambda2 {
    public static void main(String[] args) {
        execute(
                (a, b, c, d) -> {
                    System.out.println(a.toString().toUpperCase());
                    System.out.println(b.toString().toUpperCase());
                    System.out.println(c.toString().toUpperCase());
                    System.out.println(d.toString().toUpperCase());
                    return "ydunfmc";
                }
        );
    }

    public static void execute(Operations2 operations2) {
        String result = operations2.process("aaa", "bbb", "ccc", "ddd");
        System.out.println(result);
    }
}
