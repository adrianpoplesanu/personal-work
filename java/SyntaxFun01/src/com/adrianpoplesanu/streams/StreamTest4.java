package com.adrianpoplesanu.streams;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class StreamTest4 {
    public static void main(String[] args) {
        int a[] = {};
        List<Integer> numbers = Arrays.stream(a).boxed().map(e -> e + 2).collect(Collectors.toList());
        System.out.println(numbers);
    }
}
