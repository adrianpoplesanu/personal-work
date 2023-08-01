package com.adrianpoplesanu.RestTemplateDemo1.controller;

public class TestEntity {
    String aaa;

    public TestEntity() {
    }

    public String getAaa() {
        return aaa;
    }

    public void setAaa(String aaa) {
        this.aaa = aaa;
    }

    @Override
    public String toString() {
        return "TestEntity{" +
                "aaa='" + aaa + '\'' +
                '}';
    }
}
