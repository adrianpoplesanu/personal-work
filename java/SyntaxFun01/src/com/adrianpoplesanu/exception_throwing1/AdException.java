package com.adrianpoplesanu.exception_throwing1;

public class AdException extends RuntimeException {
    private AdErrorType errorType;

    public AdException(AdErrorType errorType) {
        this.errorType = errorType;
    }

    @Override
    public String getMessage() {
        return "AD ERROR: " + errorType.name();
    }
}
