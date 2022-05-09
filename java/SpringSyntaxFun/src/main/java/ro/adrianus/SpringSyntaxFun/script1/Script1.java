package ro.adrianus.SpringSyntaxFun.script1;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

import java.util.Map;

@Component
public class Script1 implements CommandLineRunner {
    @Autowired
    private Map<String, Node> nodes;

    @Override
    public void run(String... args) throws Exception {
        // ...
        nodes.entrySet().forEach(entry -> {
            System.out.println(entry.getKey() + ": " + entry.getValue());
        });
    }
}
