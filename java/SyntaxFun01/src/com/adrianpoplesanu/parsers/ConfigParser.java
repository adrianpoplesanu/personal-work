package com.adrianpoplesanu.parsers;

import java.util.Arrays;
import java.util.Map;
import java.util.stream.Collectors;

public class ConfigParser {
    private static final String config = "key1:value1,key2:value2";

    private static String getValue(String key) {
        Map<String, String> confs = Arrays.stream(config.split(",")).map(data -> data.split(":")).collect(Collectors.toMap(data -> data[0], data -> data[1]));
        if (confs.get(key) != null) return confs.get(key);
        return "oops! houston we have a problem";
    }

    public static void main(String[] args) {
        System.out.println(getValue("key1"));
        System.out.println(getValue("key2"));
        System.out.println(getValue("key3"));
    }
}
