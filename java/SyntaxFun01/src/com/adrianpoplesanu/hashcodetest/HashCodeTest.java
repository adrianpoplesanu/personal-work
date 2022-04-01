package com.adrianpoplesanu.hashcodetest;

public class HashCodeTest {

    private static int calculateFactor(String authSrc) {
        System.out.println(authSrc.hashCode());
        return Math.abs(authSrc.hashCode() % 100);
    }

    public static void main(String[] args) {
        System.out.println(calculateFactor("testAuthSrc"));
        System.out.println(calculateFactor("testAuthSrcLowHash56"));
        System.out.println(calculateFactor("testAuthSrcExempt1"));
        System.out.println(calculateFactor("testAuthSrcExempt2"));
    }
}
