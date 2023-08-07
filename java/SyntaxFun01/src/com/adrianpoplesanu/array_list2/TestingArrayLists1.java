package com.adrianpoplesanu.array_list2;

import java.util.Arrays;
import java.util.List;

public class TestingArrayLists1 {
    public static void main(String[] args) {
        List<String> names = Arrays.asList("bebe", "dex", "e", "dragut");
        System.out.println(names); // asta e fixed size
        try {
            names.remove(0);
        } catch (UnsupportedOperationException exception) {
            System.out.println("asta demonstre`a ca Arrays.asList e fixed size si un AbstractList");
        }
    }
}
