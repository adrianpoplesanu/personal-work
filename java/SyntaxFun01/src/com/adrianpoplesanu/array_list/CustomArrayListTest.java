package com.adrianpoplesanu.array_list;

public class CustomArrayListTest {
    public static void main(String[] args) {
        CustomArrayList<String> names = new CustomArrayList<>();
        names.add("buna");
        names.add("dimineata");
        names.add("!");
        names.testPrint();
    }
}
