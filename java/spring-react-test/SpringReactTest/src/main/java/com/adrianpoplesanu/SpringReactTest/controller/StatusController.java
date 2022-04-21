package com.adrianpoplesanu.SpringReactTest.controller;

import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@CrossOrigin(origins = "*", allowedHeaders = "*")
@RequestMapping("/api")
public class StatusController {
    @GetMapping("/status")
    public String status() {
        return "buna dimineata logat din google";
    }
}
