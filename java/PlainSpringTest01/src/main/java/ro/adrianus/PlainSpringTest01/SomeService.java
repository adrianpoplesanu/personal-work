package ro.adrianus.PlainSpringTest01;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;

@Service
public class SomeService {
    @Autowired
    @Qualifier("testClass2")
    SomeInterface someInterface;

    public String getAAA() {
        return someInterface.aaa();
    }
}
