package com.adrianpoplesanu.AnifScheduler;

import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;

@Configuration
public class SecurityConfig extends WebSecurityConfigurerAdapter {
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        // suprascrierea asta face ca sa nu se mai execute login-ul default
        http.csrf().disable().authorizeRequests().anyRequest().permitAll();
    }
}
