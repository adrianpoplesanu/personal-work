package com.adrianpoplesanu.DemoAnif.Model;
import org.springframework.data.cassandra.core.mapping.PrimaryKeyColumn;
import org.springframework.data.cassandra.core.mapping.Table;

@Table
public class Task {
    @PrimaryKeyColumn
    private long id;
}
