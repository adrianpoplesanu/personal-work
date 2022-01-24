package com.adrianpoplesanu.BlueAlert.service;

import org.springframework.stereotype.Service;

import java.util.HashMap;
import java.util.Map;

@Service
public class UserService {
    private Map<String, String> userMappings;

    public UserService() {
        userMappings = new HashMap<>();
    }

    public void addEntry(String uuid, String username) {
        userMappings.put(uuid, username);
    }

    public void removeEntry(String uuid) {
        userMappings.remove(uuid);
    }

    public int size() {
        return userMappings.size();
    }
}
