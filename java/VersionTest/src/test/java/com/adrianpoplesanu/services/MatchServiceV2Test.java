package com.adrianpoplesanu.services;

import org.testng.annotations.BeforeClass;
import org.testng.annotations.Test;

public class MatchServiceV2Test extends BaseMatchServiceV1Test {

    @BeforeClass(alwaysRun = true)
    public void fixVersion() {
        version = 3;
    }

    @Test
    public void testSomething3() {
        System.out.println(version);
    }
}
