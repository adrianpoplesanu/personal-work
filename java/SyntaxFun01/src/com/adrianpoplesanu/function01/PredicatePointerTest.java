package com.adrianpoplesanu.function01;

import java.util.function.Predicate;

public class PredicatePointerTest {
    private Predicate<String> callback;

    private boolean filterName(String name) {
        return name.contains("adrianus");
    }

    private boolean filterPet(String name) {
        return name.contains("bedush");
    }

    public void testPredicatePointer() {
        callback = this::filterName;
        System.out.println(callback.test("adrianus e gibutza"));
    }

    public void testPredicatePointer2() {
        callback = this::filterName;
        Predicate<String> callback2 = this::filterPet;
        System.out.println(callback.and(callback2).test("adrianus per scorillor"));
        System.out.println(callback.and(callback2).test("adrianus si bedush"));
    }
}
