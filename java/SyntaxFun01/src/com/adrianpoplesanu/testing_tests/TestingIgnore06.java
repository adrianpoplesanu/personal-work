package com.adrianpoplesanu.testing_tests;

import org.testng.annotations.Test;

public abstract class TestingIgnore06 {

    protected abstract String getVersion();

    @Test
    public void testSomething() {
        System.out.println("abstract testSomething " + getVersion());
    }

    @Test
    public void testSomethingAAA() {
        System.out.println("abstract testSomethingAA " + getVersion());
    }
}
