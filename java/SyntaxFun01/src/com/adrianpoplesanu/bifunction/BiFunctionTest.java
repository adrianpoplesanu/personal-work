package com.adrianpoplesanu.bifunction;

import java.util.function.BiConsumer;

public class BiFunctionTest {

    public void safeRun(BiConsumer<Integer, Integer> func, int val1, int val2) {
        // ...
        try {
            func.accept(val1, val2);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public void divideNumbers(int a, int b) {
        a /= b;
        System.out.println(a);
    }

    public void divideNumbers(String a, String b) {
        System.out.println(Integer.valueOf(a) / Integer.valueOf(b));
    }

    public void testDivideNumberGeneric(int a, int b) {
        //divideNumber2(a, b);
    }

    private <T, U> void divideNumber2(T t, U u) {
        System.out.println(t.getClass().getName());
        System.out.println(u);
    }

    public <T, U> void safeRun2(BiConsumer<T, U> func, T t, U u) {
        try {
            func.accept(t, u);
        } catch(Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        BiFunctionTest test = new BiFunctionTest();
        //test.safeRun(test::divideNumbers, 5, 6);
        //test.safeRun(test::divideNumbers, 6, 2);
        //test.safeRun(test::divideNumbers, 1, 0);
        //test.safeRun(test::divideNumbers, 19, 2);

        test.safeRun2(test::divideNumbers, 5, 6);
        test.safeRun2(test::divideNumbers, 10, 6);
        test.safeRun2(test::divideNumbers, "10", "3");
        test.safeRun2(test::divideNumbers, 1, 0);
        test.safeRun2(test::divideNumbers, "1", "0");
    }
}
