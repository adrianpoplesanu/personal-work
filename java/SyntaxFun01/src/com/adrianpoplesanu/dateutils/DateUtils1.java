package com.adrianpoplesanu.dateutils;

import java.util.concurrent.TimeUnit;

public class DateUtils1 {
    public static void main(String[] args) {
        System.out.println(TimeUnit.DAYS.toSeconds(90)); // 7776000 secunde in 90 de zile
        System.out.println(TimeUnit.DAYS.toSeconds(365)); // 31536000 secunde in 365 de zile
    }
}
