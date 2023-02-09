package com.adrianpoplesanu.SpringBootFiltersApplication1.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping("/adrian/endpoint2")
public class SmartController {
    @GetMapping
    @ResponseBody
    public String endpoint2() {
        return "BUNA DIMINEATA!!!";
    }
}
