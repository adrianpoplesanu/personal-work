package com.adrianpoplesanu.encoding;

import java.util.Base64;

public class TestEncoding1 {
    public static void main(String[] args) {
        byte[] decoded = Base64.getUrlDecoder().decode("LIPwImNG5vovjmwDOIZsHWxSIYRDOFaQbEGfRFM9RgA=");
        String result = "[";
        for (int i = 0; i < decoded.length; i++) {
            //System.out.println(decoded[i]);
            if (i == decoded.length - 1) {
                result += decoded[i];
            } else {
                result += decoded[i] + ", ";
            }
        }
        result += "]";
        System.out.println(result);
    }
}
