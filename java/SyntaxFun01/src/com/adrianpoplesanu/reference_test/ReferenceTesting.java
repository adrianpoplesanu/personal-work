package com.adrianpoplesanu.reference_test;

import java.util.ArrayList;

public class ReferenceTesting {
    public static void main(String[] args) {
        ListUtils listUtils = new ListUtils();
        ArrayList<Integer> numbers = new ArrayList<>();
        numbers.add(1);
        numbers.add(2);
        numbers.add(3);
        System.out.println(numbers);
        listUtils.changeList(numbers);
        System.out.println(numbers);
        listUtils.addElementToList(numbers);
        System.out.println(numbers);
        listUtils.reassignList(numbers);
        System.out.println(numbers);

        StringUtils stringUtils = new StringUtils();
        String name = "aex";
        System.out.println(name);
        stringUtils.changeString(name);
        System.out.println(name);
        stringUtils.reassignString(name);
        System.out.println(name);
    }
}
