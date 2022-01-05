package com.adrianpoplesanu.AnifScheduler;

import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;

import javax.servlet.http.HttpServletResponse;

@Configuration
public class SecurityConfig extends WebSecurityConfigurerAdapter {
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        // this prevents the default login execution
        http.csrf().disable().authorizeRequests().anyRequest().permitAll();

        // this prevents the default logout execution
        http.csrf().disable().logout(logout -> logout.permitAll()
            .logoutSuccessHandler(
                (request, response, authentication) -> {
                    response.setStatus(HttpServletResponse.SC_OK);
                }
            ));
    }
}
