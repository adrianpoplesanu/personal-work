package com.adrianpoplesanu.Reminders.Controller;

import com.sun.deploy.net.HttpResponse;
import org.springframework.http.HttpRequest;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpSession;

@Controller
public class LoginController {
    @RequestMapping(value="/authenticate", method= RequestMethod.POST)
    @ResponseBody
    String authenthicate(HttpRequest request, HttpResponse response, HttpSession session) {
        // i'm not 100% with these imports
        return "bla bla bla";
    }
}
