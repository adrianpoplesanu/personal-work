package com.adrianpoplesanu.AnifScheduler.Controller;

import com.adrianpoplesanu.AnifScheduler.Model.User;
import com.adrianpoplesanu.AnifScheduler.Service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class LoginController {
    @Autowired
    private UserService userService;

    @RequestMapping(value = "/authenticate", method = RequestMethod.POST)
    @ResponseBody
    String authenticate(@RequestParam String username, @RequestParam String password) {
        User user = userService.getUser(username, password);
        if (user == null) {
            return "NU am gasit utilizatorul :(";
        } else {
            return "am gasit utilizatorul :)";
        }
    }
}
