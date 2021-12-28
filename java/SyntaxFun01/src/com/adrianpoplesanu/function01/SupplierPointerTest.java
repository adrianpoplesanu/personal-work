package com.adrianpoplesanu.function01;

import java.util.function.Supplier;

public class SupplierPointerTest {
    private Supplier<String> callback;

    private String test() {
        return "bebe dex e frumesh";
    }

    public void testSupplierPointer() {
        callback = this::test;
        System.out.println(callback.get());
    }
}
