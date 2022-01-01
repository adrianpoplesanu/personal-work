package com.adrianpoplesanu.AnifScheduler.Repository;

import com.adrianpoplesanu.AnifScheduler.Model.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface UserRepository extends JpaRepository<User, Long> {
    User findById(int id);
    User findByEmailAndPassword(String email, String password);
}
