package objects;

import annotations.NonEmpty;
import annotations.Version;

public class Person {
    private String name;

    @NonEmpty
    @Version
    private int age;
}
