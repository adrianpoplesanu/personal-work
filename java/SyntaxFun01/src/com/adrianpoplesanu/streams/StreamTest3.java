package com.adrianpoplesanu.streams;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class StreamTest3 {
    private static int transform(int x) {
        return x + 10;
    }

    private static void test() {
        int a[] = {1, 2, 3, 4, 5};
        List<Integer> numbers = Arrays.stream(a).boxed().map(e -> transform(e)).collect(Collectors.toList());
        if (numbers.stream().filter(e -> e == 12).findFirst().isPresent()) {
            System.out.println("am un 12");
        }
        System.out.println(numbers);
    }

    public static void main(String[] args) {
        test();
    }
}
