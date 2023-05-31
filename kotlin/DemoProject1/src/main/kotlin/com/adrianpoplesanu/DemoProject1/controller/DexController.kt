package com.adrianpoplesanu.DemoProject1.controller

import org.springframework.stereotype.Controller
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.ResponseBody

@Controller()
class DexController {
    @GetMapping("/dex")
    @ResponseBody
    fun dexIndex() : String {
        return "bebe dex"
    }
}