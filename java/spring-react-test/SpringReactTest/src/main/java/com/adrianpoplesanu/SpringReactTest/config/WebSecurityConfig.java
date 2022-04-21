package com.adrianpoplesanu.SpringReactTest.config;

import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.core.Authentication;
import org.springframework.security.web.authentication.AuthenticationSuccessHandler;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Override
    protected void configure(HttpSecurity http) throws Exception {
         http.csrf().disable().authorizeRequests()
                 //.antMatchers("/", "/home").permitAll()
                 .antMatchers("/login").permitAll()
                 .anyRequest().authenticated()
                 .and()
                 .oauth2Login()
                 .loginPage("/login")
                 .successHandler(new AuthenticationSuccessHandler() {

                     @Override
                     public void onAuthenticationSuccess(HttpServletRequest request, HttpServletResponse response,
                                                         Authentication authentication) throws IOException, ServletException {
                         System.out.println("AuthenticationSuccessHandler invoked");
                         System.out.println("Authentication name: " + authentication.getPrincipal().toString());
                         //CustomOAuth2User oauthUser = (CustomOAuth2User) authentication.getPrincipal();

                         //userService.processOAuth2PostLogin(oauthUser.getEmail());

                         response.sendRedirect("/");
                     }
                 });
    }
}
