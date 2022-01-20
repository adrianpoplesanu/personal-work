package com.adrianpoplesanu.streams;

import java.util.ArrayList;
import java.util.List;

public class StreamTest1 {
    public static void main(String[] args) {
        List<String> words = new ArrayList<>();
        words.add("bebe");
        words.add("dex");
        words.add("e");
        words.add("frumesh");
        words.stream().forEach(x -> System.out.println(x.toUpperCase()));
        System.out.println(words);
    }
}
