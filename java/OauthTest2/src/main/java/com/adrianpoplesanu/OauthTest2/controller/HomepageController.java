package com.adrianpoplesanu.OauthTest2.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping("/pages")
public class HomepageController {
    @GetMapping("/home")
    @ResponseBody
    String index() {
        return "home page, welcome";
    }
}
