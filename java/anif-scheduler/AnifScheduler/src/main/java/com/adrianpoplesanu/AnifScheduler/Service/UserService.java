package com.adrianpoplesanu.AnifScheduler.Service;

import com.adrianpoplesanu.AnifScheduler.Model.User;
import com.adrianpoplesanu.AnifScheduler.Repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class UserService {
    @Autowired
    private UserRepository userRepository;

    public User getUser(int id) {
        return userRepository.findById(id);
    }

    public User getUser(String email, String password) {
        return userRepository.findByEmailAndPassword(email, password);
    }
}
