package com.adrianpoplesanu.Reminders.Repository;

import com.adrianpoplesanu.Reminders.Model.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface UserRepository extends JpaRepository<User, Long> {
    List<User> findByUsernameAndPassword(String username, String password);
}
