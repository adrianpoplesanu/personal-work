package com.adrianpoplesanu.SpringReactTest.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.security.Principal;

@RestController
@RequestMapping("/user")
public class UserDetails {
    @GetMapping("/info")
    String info(Principal principal) {
        return principal.getName();
    }
}
