package com.adrianpoplesanu.AOPTester4;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

@Component
public class Tester implements CommandLineRunner {

    @Autowired
    private Worker worker;

    @Override
    public void run(String... args) throws Exception {
        System.out.println("running code in Spring context");
        worker.work();
    }
}
