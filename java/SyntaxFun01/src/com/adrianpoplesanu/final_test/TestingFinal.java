package com.adrianpoplesanu.final_test;

public class TestingFinal {
    public static void main(String[] args) {
        MapWrapper mapWrapper = new MapWrapper();
        mapWrapper.setFields("bebe dex", "12");
        mapWrapper.setFields("adish", "38");
        mapWrapper.setFields("ramunic", "34");
        System.out.println(mapWrapper.getFields());
    }
}
