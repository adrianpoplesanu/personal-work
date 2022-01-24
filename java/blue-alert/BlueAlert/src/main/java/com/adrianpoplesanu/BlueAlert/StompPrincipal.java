package com.adrianpoplesanu.BlueAlert;

import com.adrianpoplesanu.BlueAlert.model.User;

import java.security.Principal;

public class StompPrincipal implements Principal {
    public String name;
    public User user;

    public StompPrincipal(String name) {
        this.name = name;
    }

    @Override
    public String getName() {
        return name;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }
}
