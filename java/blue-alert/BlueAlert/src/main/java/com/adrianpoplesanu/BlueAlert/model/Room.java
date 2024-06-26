package com.adrianpoplesanu.BlueAlert.model;

import java.util.List;

public class Room {
    private String name;
    private List<User> users;

    public Room() {

    }

    public Room(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<User> getUsers() {
        return users;
    }

    public void setUsers(List<User> users) {
        this.users = users;
    }
}
