package com.adrianpoplesanu.reflection;

import java.lang.reflect.Method;
import java.util.Stack;

public class ReflectionTest {
    public static void test() {
        try {
            Class c = Class.forName("java.util.Stack");
            Method m[] = c.getDeclaredMethods();
            for (int i = 0; i < m.length; i++)
                System.out.println(m[i].toString());
        }
        catch (Throwable e) {
            System.err.println(e);
        }
    }

    public static void main(String[] args) {
        System.out.println("buna dimineata...");
        test();
        Stack<String> a;
    }
}
