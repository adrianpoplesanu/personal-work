package com.adrianpoplesanu.optional_testing1;

import java.util.Optional;

public class OptionalTesting1 {

    class Name {
        public String name;
    }

    public Optional<Name> getName(int a) {
        Name name;
        if (a > 30) {
            name = new Name();
            name.name = "bbb";
        } else {
            name = null;
        }
        return Optional.ofNullable(name);
    }

    public static void main(String[] args) {
        OptionalTesting1 optionalTesting1 = new OptionalTesting1();
        Optional<Name> result = optionalTesting1.getName(5);
        System.out.println(result.isPresent() && result.get().name.contains("aaa"));
    }
}
