package com.adrianpoplesanu.DemoAnif.Controllers;

import com.adrianpoplesanu.DemoAnif.Services.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.net.URLEncoder;

@Controller
public class LoginController {

    @Autowired
    private UserService userService;

    @PostMapping("/login")
    @ResponseBody
    String login(HttpServletResponse response, HttpSession session) throws IOException {
        String val = (String) session.getAttribute("aaa");
        System.out.println(val);
        System.out.println(userService.getUser("bedush"));
        Cookie cookie = new Cookie("mesaj", URLEncoder.encode("bebe desh e un frumesh", "UTF-8" ));
        response.addCookie(cookie);
        if (val == null || val.equals("")) {
            session.setAttribute("aaa", "adrianus per scorillo");
        }
        return "am primit credentialele";
    }

    @GetMapping("/logout")
    @ResponseBody
    String logout(HttpSession session) {
        session.invalidate();
        return "session invalidated";
    }

    @GetMapping("/logout2")
    @ResponseBody
    String logout2(HttpSession session) {
        session.invalidate();
        return "session invalidated";
    }
}
