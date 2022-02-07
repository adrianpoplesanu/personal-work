package com.adrianpoplesanu.lamdas;

public class PrintableTester {
    public static void main(String[] args) {
        print(() -> "teeest");
    }

    public static void print(Printable printable) {
        System.out.println(printable.print());
    }
}
