package com.adrianpoplesanu.DemoAnif.Service;

import com.adrianpoplesanu.DemoAnif.Model.User;
import com.adrianpoplesanu.DemoAnif.Repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class UserService {

    @Autowired
    private UserRepository userRepository;

    public String getUser(String username) {
        long i = 0;
        Optional<User> user = userRepository.findById(i);
        // user.get()
        return username + " per scorillo";
    }

    public User authenticateCredentials(String username, String password) {
        List<User> users = userRepository.findByEmailAndPassword(username, password);
        if (users.size() != 1) {
            return null;
        }
        return users.get(0);
    }
}
