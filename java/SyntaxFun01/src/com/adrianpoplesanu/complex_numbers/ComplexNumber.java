package com.adrianpoplesanu.complex_numbers;

public class ComplexNumber {
    private float re;
    private float im;

    public ComplexNumber(float re, float im) {
        this.re = re;
        this.im = im;
    }

    public float getRe() {
        return re;
    }

    public void setRe(float re) {
        this.re = re;
    }

    public float getIm() {
        return im;
    }

    public void setIm(float im) {
        this.im = im;
    }

    public String toString() {
        return re + "+" + im + "i";
    }
}
