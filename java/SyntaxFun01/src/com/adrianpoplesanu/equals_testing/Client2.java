package com.adrianpoplesanu.equals_testing;

import java.util.Objects;

public class Client2 {
    private String name;
    private int age;

    public Client2(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Client2 client2 = (Client2) o;
        return age == client2.age && Objects.equals(name, client2.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, age);
    }
}
