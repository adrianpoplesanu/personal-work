package com.adrianpoplesanu.reference_test;

import java.util.ArrayList;
import java.util.List;

public class ListUtils {
    public void changeList(List<Integer> numbers) {
        numbers.set(1, 77);
    }

    public void addElementToList(List<Integer> numbers) {
        numbers.add(99);
    }

    public void reassignList(List<Integer> numbers) {
        numbers = new ArrayList<>();
        numbers.add(11);
        numbers.add(22);
        numbers.add(33);
        System.out.println(numbers);
    }
}
