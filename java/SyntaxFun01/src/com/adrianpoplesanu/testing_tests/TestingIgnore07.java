package com.adrianpoplesanu.testing_tests;

import org.testng.annotations.Ignore;

@Ignore("some message here")
public class TestingIgnore07 extends TestingIgnore06 {
    @Override
    protected String getVersion() {
        return "v1";
    }
}
