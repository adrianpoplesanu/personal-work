package com.adrianpoplesanu.iterables_test;

import com.google.common.collect.Iterables;

import java.util.ArrayList;
import java.util.List;

public class IterablesTest {
    public static void main(String[] args) {
        List<String> names = new ArrayList<>();
        for (int i = 0; i < 100; i++) {
            names.add("dex" + (i > 9 ? i : "0" + i));
        }
        for (List<String> batch : Iterables.partition(names, 10)) {
            System.out.println(batch);
        }
    }
}
