package com.adrianpoplesanu.Reminders.Service;

import com.adrianpoplesanu.Reminders.Model.User;
import com.adrianpoplesanu.Reminders.Repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class UserService {
    @Autowired
    private UserRepository userRepository;

    public List<User> getUser(String username, String password) {
        return userRepository.findByUsernameAndPassword(username, password);
    }
}
