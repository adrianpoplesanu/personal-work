package com.adrianpoplesanu.testing_tests;

import org.testng.annotations.Test;

public class TestingIgnore08 extends TestingIgnore06 {
    @Override
    protected String getVersion() {
        return "v2";
    }

    @Test
    public void testSomething2() {
        System.out.println("testSomething2");
    }
}
