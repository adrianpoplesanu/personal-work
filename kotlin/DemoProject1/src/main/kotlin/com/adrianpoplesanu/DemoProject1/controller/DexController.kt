package com.adrianpoplesanu.DemoProject1.controller

import org.springframework.stereotype.Controller
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.PostMapping
import org.springframework.web.bind.annotation.RequestBody
import org.springframework.web.bind.annotation.ResponseBody

@Controller()
class DexController {
    @GetMapping("/dex")
    @ResponseBody
    fun getDex() : String {
        return "bebe dex <form method=\"POST\"><input type=\"hidden\" id=\"fname\" name=\"fname\" value=\"some text here\"></input><button type=\"submit\">Click here for POST</button></form>"
    }

    @PostMapping("/dex")
    @ResponseBody
    fun createDex(@RequestBody fname: String) : String {
        return "bebe dex post: $fname"
    }
}