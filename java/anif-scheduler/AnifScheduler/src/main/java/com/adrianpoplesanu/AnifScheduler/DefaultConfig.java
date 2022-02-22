package com.adrianpoplesanu.AnifScheduler;

import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class DefaultConfig {
    @Bean
    public TestBean testBean() {
        return new TestBeanConcrete("prefix1");
    }

    @Bean
    @Qualifier("testBean")
    public TestBean testBean2() {
        return new TestBeanConcrete("prefix2");
    }
}
