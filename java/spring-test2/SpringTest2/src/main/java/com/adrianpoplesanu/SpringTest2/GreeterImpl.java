package com.adrianpoplesanu.SpringTest2;

import org.springframework.stereotype.Component;

@Component
public class GreeterImpl implements Greeter {

    @Override
    public String hello() {
        return "buna dimineata!";
    }
}
