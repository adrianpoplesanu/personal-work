package com.adrianpoplesanu.services;

import org.testng.annotations.BeforeClass;
import org.testng.annotations.Test;

public class BaseMatchServiceV1Test extends BaseTest {

    @BeforeClass(alwaysRun = true)
    public void fixVersion() {
        version = 77;
    }

    @BeforeClass(alwaysRun = true)
    public void setup() {
        version = 2;
    }

    @Test
    public void testSomething2() {
        System.out.println(version);
    }
}
