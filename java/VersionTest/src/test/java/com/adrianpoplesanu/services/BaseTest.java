package com.adrianpoplesanu.services;

import org.testng.annotations.BeforeClass;
import org.testng.annotations.Test;

public class BaseTest {
    int version;

    @BeforeClass(alwaysRun = true)
    public void fixVersion() {
        version = 55;
    }

    @Test
    public void testSomething1() {
        System.out.println(version);
    }
}
