package com.adrianpoplesanu.SpringBootFiltersApplication1.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping("/adi/endpoint1")
public class DummyController {
    @GetMapping
    @ResponseBody
    public String endpoint1() {
        return "buna dimineata!";
    }
}
