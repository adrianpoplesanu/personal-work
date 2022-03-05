package com.adrianpoplesanu.streams;

import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class StreamTest2 {
    public static void main(String[] args) {
        List<String> keys = Arrays.asList("key1", "key2", "key3");
        List<String> values = Arrays.asList("value1", "value2", "value3");

        Map<String, String> mappings = IntStream.range(0, keys.size())
                .boxed()
                .collect(Collectors.toMap(keys::get, values::get));

        System.out.println(mappings);
    }
}
