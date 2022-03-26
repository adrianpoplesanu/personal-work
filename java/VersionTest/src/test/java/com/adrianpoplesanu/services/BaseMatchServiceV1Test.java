package com.adrianpoplesanu.services;

import org.testng.annotations.BeforeClass;
import org.testng.annotations.Test;

public class BaseMatchServiceV1Test {
    int version;

    @BeforeClass(alwaysRun = true)
    protected void setVersion() {
        version = 1;
    }

    @BeforeClass(alwaysRun = true)
    public void setup() {
        version = 1;
    }

    @Test
    public void testSomething() {
        System.out.println(version);
    }
}
