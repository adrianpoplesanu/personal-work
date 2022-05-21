package com.adrianpoplesanu.streams;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class StreamTest5 {

    private static class Person {
        private String name;

        public Person(String name) {
            this.name = name;
        }

        public String getName() {
            return "Person [" + name + "]";
        }
    }

    private static Person toPerson(String name) {
        return new Person(name);
    }

    public static void main(String[] args) {
        String names[] = {"aaa", "bbb", "ccc"};
        List<Person> persons = Arrays.stream(names).map(name -> toPerson(name)).collect(Collectors.toList());
        persons.stream().forEach(person -> System.out.println(person.getName()));

        List<String> a = Collections.emptyList();
        // a.add("buna dimineata!"); // this doesn't work
        System.out.println(a);
    }
}
