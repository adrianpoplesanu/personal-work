package com.adrianpoplesanu.DemoAnif.Services;

import org.springframework.stereotype.Service;

@Service
public class UserService {
    public String getUser(String username) {
        return username + " per scorillo";
    }
}
