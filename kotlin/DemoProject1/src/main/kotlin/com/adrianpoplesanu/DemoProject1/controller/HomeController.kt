package com.adrianpoplesanu.DemoProject1.controller

import org.springframework.stereotype.Controller
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.ResponseBody

@Controller
class HomeController {
    @GetMapping("/")
    @ResponseBody
    fun index() : String {
        return "aaa"
    }

    @GetMapping("test2")
    @ResponseBody
    fun test2() : String {
        val text = this::class.java.classLoader.getResource("test.csv").readText()
        return text
    }
}