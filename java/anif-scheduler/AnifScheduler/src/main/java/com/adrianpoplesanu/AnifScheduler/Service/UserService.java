package com.adrianpoplesanu.AnifScheduler.Service;

import com.adrianpoplesanu.AnifScheduler.Model.User;
import com.adrianpoplesanu.AnifScheduler.Repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

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

    public List<User> getUsers() {
        return userRepository.findAll();
    }

    public void addUser(User user) {
        userRepository.save(user);
    }

    public void deleteUser(int userId) {
        User user = getUser(userId);
        userRepository.delete(user);
    }
}
