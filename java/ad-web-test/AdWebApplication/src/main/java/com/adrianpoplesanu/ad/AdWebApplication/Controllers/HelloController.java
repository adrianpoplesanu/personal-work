package com.adrianpoplesanu.ad.AdWebApplication.Controllers;

import com.adrianpoplesanu.ad.AdWebApplication.Models.User;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HelloController {
    @GetMapping("/")
    public String index() {
        return "Greetings for Ad Language Web Platform!";
    }

    @GetMapping("/check2")
    public String check2() {
        return "Status: 200 OKish!";
    }

    @GetMapping("/json-test")
    public User json_test() {
        User user = new User("adish", 1);
        return user;
        //return new JSONObject("{'aa':'bb'}");
    }
}
