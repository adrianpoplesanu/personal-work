package com.adrianpoplesanu.parsers;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class ParserChecker {
    public static void test() {
        /*ArrayList<Integer> numbers = new ArrayList<>();
        numbers.add(1);
        numbers.add(2);
        numbers.add(3);
        numbers.add(4);
        numbers.add(5);*/
        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7);

        List<Integer> result = new ArrayList<>();

        //numbers.stream().forEach(e -> { if(e % 2 == 0) result.add(e);});
        //numbers.stream().filter(e -> e % 2 == 0).forEach(e -> result.add(e));
        result = numbers.stream().filter(e -> e % 2 == 0).collect(Collectors.toList());

        System.out.println(result.getClass().getTypeName());
        System.out.println(result);
    }

    public static List<Integer> test2(List<Integer> numbers) {
        List<Integer> result = new ArrayList<>();
        if (numbers.stream().filter(e -> e == 6).findAny().isPresent()) return result;
        //numbers.forEach(e -> result.add(e));
        result = numbers.stream().collect(Collectors.toList());
        return result;
    }

    public static void test3() {
        List<Integer> numbers = Arrays.asList(1, 2, 6, 7);
        System.out.println(test2(numbers));
        numbers = Arrays.asList(1, 3, 5, 7);
        System.out.println(test2(numbers));
    }

    public static void main(String[] args) {
        test3();
    }
}
