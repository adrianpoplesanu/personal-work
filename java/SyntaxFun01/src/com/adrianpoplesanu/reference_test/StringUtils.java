package com.adrianpoplesanu.reference_test;

public class StringUtils {
    public void changeString(String target) {
        System.out.println("changeString(): " + target);
        target.replace('a', 'd');
        System.out.println("changeString(): " + target);
    }

    public void reassignString(String target) {
        System.out.println("reassignString(): " + target);
        target = "bebe dex";
        System.out.println("reassignString(): " + target);
    }
}
