package com.adrianpoplesanu.bifunction;

import java.util.function.BiConsumer;

public class BiFunctionTest2 {

    public void divideNumbers(int a, int b) {
        System.out.println(a / b);
    }

    public void divideNumbers(String a, String b) {
        System.out.println(Integer.valueOf(a) / Integer.valueOf(b));
    }

    public <T, U> void safeRun(BiConsumer<T, U> consumer, T t, U u) {
        try {
            consumer.accept(t, u);
        } catch (Exception e) {
            System.out.println("Error running function. Reason: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        BiFunctionTest2 biFunctionTest = new BiFunctionTest2();
        biFunctionTest.safeRun(biFunctionTest::divideNumbers, 10, 4);
        biFunctionTest.safeRun(biFunctionTest::divideNumbers, "10", "4");
        biFunctionTest.safeRun(biFunctionTest::divideNumbers, 1, 0);
        biFunctionTest.safeRun(biFunctionTest::divideNumbers, "1", "0");
    }
}
