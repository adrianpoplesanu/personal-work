package com.adrianpoplesanu.services;

import org.testng.annotations.BeforeClass;

public class MatchServiceV2Test extends BaseMatchServiceV1Test {

    @BeforeClass(alwaysRun = true)
    protected void setVersion() {
        version = 2;
    }
}
