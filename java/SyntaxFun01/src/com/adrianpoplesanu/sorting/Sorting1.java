package com.adrianpoplesanu.sorting;

import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Sorting1 {
    public static void main(String[] args) {
        Map<String, String> elements = new HashMap<>();
        elements.put("t", "1");
        elements.put("Test", "2");
        elements.put("u", "3");
        System.out.println(elements);

        List<String> keys = elements.keySet().stream().collect(Collectors.toList());
        Collections.sort(keys, String.CASE_INSENSITIVE_ORDER);
        System.out.println(keys);

        elements.keySet().stream().sorted().forEach(key -> {
            System.out.println(elements.get(key));
        });
    }
}
