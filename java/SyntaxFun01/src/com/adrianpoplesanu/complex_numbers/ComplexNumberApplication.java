package com.adrianpoplesanu.complex_numbers;

public class ComplexNumberApplication {
    public static void main(String[] args) {
        Addable addable = (a, b) -> new ComplexNumber(a.getRe() + b.getRe(), a.getIm() + b.getIm());

        ComplexNumber c1 = new ComplexNumber(1, 2);
        ComplexNumber c2 = new ComplexNumber(2, 3);

        System.out.println(addable.add(c1, c2));
    }
}
