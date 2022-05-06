package com.adrianpoplesanu.AOPTester2.controller;

import com.adrianpoplesanu.AOPTester2.aspect.DoNothing;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class Homepage {
    @GetMapping("/")
    @ResponseBody
    @DoNothing
    public String index() {
        return "buna dimineata!";
    }
}
