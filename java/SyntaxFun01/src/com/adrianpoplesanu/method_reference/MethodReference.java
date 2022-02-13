package com.adrianpoplesanu.method_reference;

public class MethodReference {

    private String convert(int a, int b) {
        return "aaa" + (a + b * 2);
    }

    private String convert2(String a, String b) {
        return a + b.toUpperCase() + a;
    }

    public static void main(String[] args) {
        MethodReference methodReference = new MethodReference();
        Converter conv = methodReference::convert;
        String result = conv.convert(11,3);
        System.out.println(result);


        // result = methodReference::convert2("aaa", "bbb"); // this does not work
        // however this does:
        Converter2 conv2 = methodReference::convert2;
        result = conv2.test("aaa", "bbb");
        System.out.println(result);
    }
}
