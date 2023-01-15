package com.adrianpoplesanu.stack_trace;

public class StackTraceTesting {
    public static void main(String[] args) {
        //...
        StackTraceElement[] stackTrace = Thread.currentThread().getStackTrace();
        System.out.println(stackTrace.length);

        for (StackTraceElement element : stackTrace) {
            System.out.println(element);
            System.out.println(element.getClassName());
        }
    }
}
