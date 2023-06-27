package com.adrianpoplesanu.testing_tests;

import org.testng.annotations.Ignore;
import org.testng.annotations.Test;

@Ignore
public class TestingIgnore02 extends TestingIgnore01{
    @Test
    public void testSomething2() {
        System.out.println("testSomething2()");
    }
}
