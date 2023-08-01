package com.adrianpoplesanu.empty_list_test;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class EmptyListTest {
    public static void main(String[] args) {
        //List<Object> elements = Collections.emptyList(); // this won't work
        List<Object> elements = new ArrayList<>(); // this will work
        elements.add("buna");
        elements.add("dimineata");
        elements.add("bebe");
        elements.add("dex");
        System.out.println(elements);
    }
}
