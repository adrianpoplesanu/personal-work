package com.adrianpoplesanu.AnifScheduler.Models.Status;

public class StatusModel {
    public int code;
    public String message;

    public StatusModel(int code, String message) {
        this.code = code;
        this.message = message;
    }
}
