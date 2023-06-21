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

    @GetMapping("test3")
    @ResponseBody
    fun test3() : String {
        val text = this::class.java.classLoader.getResourceAsStream("test.csv").bufferedReader().readText()
        return text
    }

    @GetMapping("test4")
    @ResponseBody
    fun test4() : String {
        val text = this.javaClass.classLoader.getResourceAsStream("test.csv").bufferedReader().readText()
        return text
    }
}