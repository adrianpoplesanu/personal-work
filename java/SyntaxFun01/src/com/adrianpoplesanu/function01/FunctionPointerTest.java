package com.adrianpoplesanu.function01;

import java.util.function.Function;

public class FunctionPointerTest {
    Function<String, Integer> callback;

    private int test(String param) {
        System.out.println(param);
        return 12;
    }

    public void testFunctionMethod() {
        callback = this::test;
        int res = callback.apply("buna dimineata");
        System.out.println(res);
    }
}
