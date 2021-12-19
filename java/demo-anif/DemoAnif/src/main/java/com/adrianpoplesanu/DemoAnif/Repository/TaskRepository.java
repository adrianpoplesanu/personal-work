package com.adrianpoplesanu.DemoAnif.Repository;

import com.adrianpoplesanu.DemoAnif.Model.Task;
import org.springframework.data.cassandra.repository.CassandraRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface TaskRepository extends CassandraRepository<Task, Long> {
}
