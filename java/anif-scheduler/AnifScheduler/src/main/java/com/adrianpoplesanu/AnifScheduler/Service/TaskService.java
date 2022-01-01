package com.adrianpoplesanu.AnifScheduler.Service;

import com.adrianpoplesanu.AnifScheduler.Repository.TaskRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class TaskService {
    @Autowired
    private TaskRepository taskRepository;
}
