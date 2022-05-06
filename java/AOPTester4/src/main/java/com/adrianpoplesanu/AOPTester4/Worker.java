package com.adrianpoplesanu.AOPTester4;

import org.springframework.stereotype.Component;

@Component
public class Worker {
    public void work() {
        System.out.println("in Worker.work()");
    }
}
