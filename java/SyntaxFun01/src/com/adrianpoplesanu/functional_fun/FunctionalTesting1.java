package com.adrianpoplesanu.functional_fun;

import java.util.function.Supplier;

public class FunctionalTesting1 {

    private <T> T handleError (Supplier<T> supplier) {
        return supplier.get();
    }

    private void handleError (Runnable runnable) {
        runnable.run();
    }

    private String checkSomething (String name) {
        // this returns something
        return name;
    }

    private void checkSomething2() {
        // this doesn't return anything
        System.out.println("bebe dutza");
    }

    public void testing1() {
        String val = handleError(() -> checkSomething("bebe dex"));
        System.out.println(val);
    }

    public void testing2() {
        handleError(() -> checkSomething2());
    }

    public static void main(String[] args) {
        FunctionalTesting1 functionalTesting1 = new FunctionalTesting1();
        functionalTesting1.testing1();
        functionalTesting1.testing2();
    }
}
