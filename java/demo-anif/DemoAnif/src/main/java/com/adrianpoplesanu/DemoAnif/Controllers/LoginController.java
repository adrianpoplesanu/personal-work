package com.adrianpoplesanu.DemoAnif.Controllers;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpSession;

@Controller
public class LoginController {
    @PostMapping("/login")
    @ResponseBody
    String login(HttpSession session) {
        return "am primit credentialele";
    }
}
