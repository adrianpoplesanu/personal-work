package com.adrianpoplesanu.DemoProject1.controller

import org.springframework.stereotype.Controller
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.PostMapping
import org.springframework.web.bind.annotation.ResponseBody

@Controller()
class DexController {
    @GetMapping("/dex")
    @ResponseBody
    fun getDex() : String {
        return "bebe dex"
    }

    @PostMapping("/dex")
    @ResponseBody
    fun createDex() : String {
        return "bebe dex post"
    }
}