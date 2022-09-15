package ro.adrianus.PlainSpringTest01;

import org.springframework.stereotype.Component;

@Component(value = "testClass1")
public class TestClass1 implements SomeInterface {
    public String aaa() {
        return "aaa";
    }
}
