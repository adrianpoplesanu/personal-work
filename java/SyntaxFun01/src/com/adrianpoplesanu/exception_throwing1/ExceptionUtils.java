package com.adrianpoplesanu.exception_throwing1;

public class ExceptionUtils {
    public static void assertNotNull(Object object, String message, AdErrorType errorType) {
        if (object == null) {
            System.out.println("LOG: " + message);
            throw new AdException(errorType);
        }
    }
}
