package com.adrianpoplesanu.RestTemplateDemo1.controller;

import java.util.List;

public class ResponseMessage {
    String code;
    String value;

    List<Object> messages;

    public ResponseMessage() {

    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    public List<Object> getMessages() {
        return messages;
    }

    public void setMessages(List<Object> messages) {
        this.messages = messages;
    }

    @Override
    public String toString() {
        return "ResponseMessage{" +
                "code='" + code + '\'' +
                ", value='" + value + '\'' +
                '}';
    }
}
