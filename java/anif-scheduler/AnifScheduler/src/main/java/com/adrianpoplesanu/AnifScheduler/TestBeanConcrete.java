package com.adrianpoplesanu.AnifScheduler;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

//@Component // un-comment this to make TestBeanConcrete injectable, also un-comment testBeanConcrete from StatusController
public class TestBeanConcrete implements TestBean {
    private String prefix;

    public TestBeanConcrete(@Value("defaultprefix") String prefix) {
        this.prefix = prefix;
    }

    @Override
    public String data() {
        return prefix + "some data here";
    }
}
