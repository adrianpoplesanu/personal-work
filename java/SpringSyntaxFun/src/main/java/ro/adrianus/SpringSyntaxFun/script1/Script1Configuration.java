package ro.adrianus.SpringSyntaxFun.script1;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.HashMap;
import java.util.Map;

@Configuration
public class Script1Configuration {
    @Bean
    public Map getNodes() {
        Map<String, Node> result = new HashMap<>();
        result.put("a1", box1());
        result.put("a2", box2());
        return result;
    }

    @Bean
    public Box1 box1() {
        return new Box1();
    }

    @Bean
    public Box2 box2() {
        return new Box2();
    }
}
