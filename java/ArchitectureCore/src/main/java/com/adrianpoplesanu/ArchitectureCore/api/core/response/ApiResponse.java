package com.adrianpoplesanu.ArchitectureCore.api.core.response;

public class ApiResponse<T> {
    private T data;

    public ApiResponse() {
        data = null;
    }

    public ApiResponse(T data) {
        this.data = data;
    }

    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }
}
