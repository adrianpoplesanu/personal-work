package com.adrianpoplesanu.filtering_test;

import java.util.Arrays;
import java.util.Collection;
import java.util.stream.Collectors;

public class FilteringTest1 {
    public static void main(String[] args) {
        Collection<String> names = Arrays.asList("aaa", "bbb", "ccc", "dddbbb");
        Collection<String> results = Arrays.asList("bbb", "dddbbb");
        Collection<String> upperResults = results.stream()
                .filter(result -> result.contains("bbb"))
                .map(e -> e.toUpperCase())
                .collect(Collectors.toList());

        System.out.println(upperResults);

        for (String name : names) {
            if (!upperResults.stream()
                    .filter(e -> e.equals(name.toUpperCase()))
                    .findFirst()
                    .isPresent()) {
                System.out.println(name + " was not found");
            }
        }
    }
}
