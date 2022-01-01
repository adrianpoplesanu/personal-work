package com.adrianpoplesanu.AnifScheduler.Repository;

import com.adrianpoplesanu.AnifScheduler.Model.Task;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface TaskRepository extends JpaRepository<Task, Long> {
}
