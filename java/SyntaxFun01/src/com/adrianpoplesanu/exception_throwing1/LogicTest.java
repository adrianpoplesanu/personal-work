package com.adrianpoplesanu.exception_throwing1;

public class LogicTest {
    public void testFunctionality() {
        //ExceptionUtils.assertNotNull(null, "oops - some message 1", AdErrorType.NOT_FOUND);
        //ExceptionUtils.assertNotNull(null, "oops - some message 2", AdErrorType.INVALID_CHARACTERS);
        //ExceptionUtils.assertNotNull(null, "oops - some message 3", AdErrorType.MAX_LIMIT_REACHED);
        ExceptionUtils.assertNotNull("aaa", "oops - some message 1", AdErrorType.NOT_FOUND);
        ExceptionUtils.assertNotNull("bbb", "oops - some message 2", AdErrorType.INVALID_CHARACTERS);
        ExceptionUtils.assertNotNull("ccc", "oops - some message 3", AdErrorType.MAX_LIMIT_REACHED);
    }
}
