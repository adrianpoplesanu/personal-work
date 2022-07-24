package com.adrianpoplesanu.OauthTest2.config;

import org.springframework.security.config.annotation.method.configuration.EnableGlobalMethodSecurity;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.config.http.SessionCreationPolicy;

/*@EnableWebSecurity
@EnableGlobalMethodSecurity(prePostEnabled = true)*/
public class SecurityConfiguration extends WebSecurityConfigurerAdapter {
    /*@Override
    protected void configure(final HttpSecurity http) throws Exception {
        // https://docs.spring.io/spring-security/reference/
        // https://stackoverflow.com/questions/58805033/using-spring-boot-2-oauth-client-and-resourceserver-in-the-same-context
        http.authorizeRequests()
                .antMatchers("/admin/**").fullyAuthenticated()
                .and()
                .sessionManagement().sessionCreationPolicy(SessionCreationPolicy.STATELESS)
                .and()
                .oauth2ResourceServer().jwt()
                .and()
                .and()
                .cors().and().csrf().disable();
    }*/
}
