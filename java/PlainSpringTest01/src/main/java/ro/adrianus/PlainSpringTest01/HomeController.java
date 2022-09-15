package ro.adrianus.PlainSpringTest01;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class HomeController {

    @Autowired
    TestClass1 testClass1;

    @GetMapping("/")
    @ResponseBody
    public String index() {
        return testClass1.aaa();
    }
}
