package com.adrianpoplesanu.ModuleTest04;

import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.PropertySource;

@Configuration
@PropertySource("classpath:test.properties")
public class SimpleJavaConfig {
    public SimpleJavaConfig() {
        super();
    }
}
