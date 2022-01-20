package com.adrianpoplesanu.streams;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class StreamTest1 {
    public static void main(String[] args) {
        List<String> words = new ArrayList<>();
        words.add("bebe");
        words.add("dex");
        words.add("e");
        words.add("frumesh");
        words.stream().forEach(x -> System.out.println(x.toUpperCase()));
        List<String> keywords = words.stream().map(x -> x.toUpperCase()).filter(x -> true).collect(Collectors.toList());
        System.out.println(keywords);
    }
}
