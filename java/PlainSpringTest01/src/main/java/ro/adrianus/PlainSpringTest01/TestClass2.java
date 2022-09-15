package ro.adrianus.PlainSpringTest01;

import org.springframework.stereotype.Component;

@Component(value = "testClass2")
public class TestClass2 implements SomeInterface {

    @Override
    public String aaa() {
        return "bbb";
    }
}
