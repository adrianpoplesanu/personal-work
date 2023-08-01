package com.adrianpoplesanu.RestTemplateDemo1.controller;

public class ErrorMessage {
    String code;
    String info;

    public ErrorMessage(String code, String info) {
        this.code = code;
        this.info = info;
    }

    @Override
    public String toString() {
        return "{" +
                "code=" + code +
                ", info=" + info +
                '}';
    }
}
