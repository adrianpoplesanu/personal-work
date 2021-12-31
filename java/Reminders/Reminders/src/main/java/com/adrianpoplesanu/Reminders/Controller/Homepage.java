package com.adrianpoplesanu.Reminders.Controller;

import com.adrianpoplesanu.Reminders.Model.User;
import com.adrianpoplesanu.Reminders.Service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.servlet.view.RedirectView;

import java.util.List;

@Controller
public class Homepage {
    @Autowired
    private UserService userService;

    @RequestMapping(value="/", method=RequestMethod.GET)
    @ResponseBody
    public User index() {
        List<User> users = userService.getUser("adrianus@adrianus.ro", "aaa");
        if (users == null || users.isEmpty()) {
            return new User();
        }
        return users.get(0);
        //return "bebe dex e frumesh";
    }

    @RequestMapping(value="/test", method=RequestMethod.GET)
    public String test() {
        return "homepage";
    }

    @RequestMapping(value="/test-redirect", method=RequestMethod.GET)
    public RedirectView testRedirect() {
        return new RedirectView("/test");
    }
}
