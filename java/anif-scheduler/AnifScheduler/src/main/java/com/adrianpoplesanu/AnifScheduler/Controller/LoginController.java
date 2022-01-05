package com.adrianpoplesanu.AnifScheduler.Controller;

import com.adrianpoplesanu.AnifScheduler.Model.User;
import com.adrianpoplesanu.AnifScheduler.Service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;
import org.springframework.web.servlet.view.RedirectView;

import javax.servlet.http.HttpSession;

@Controller
public class LoginController {
    @Autowired
    private UserService userService;

    @RequestMapping(value = "/authenticate", method = RequestMethod.POST)
    RedirectView authenticate(@RequestParam String username, @RequestParam String password, HttpSession session, RedirectAttributes attributes) {
        User user = userService.getUser(username, password);

        //ModelAndView modelAndView = new ModelAndView();
        if (user == null) {
            //modelAndView.setViewName("homepage");
            attributes.addAttribute("errorMessage", "Wrong username or password.");
            return new RedirectView("/");
        } else {
            session.setAttribute("username", user.getEmail());
            return new RedirectView("/");
        }
    }

    @RequestMapping(value = "/logout2", method = RequestMethod.GET)
    RedirectView logout(HttpSession session) {
        ModelAndView modelAndView = new ModelAndView("logout");
        session.removeAttribute("username");
        return new RedirectView("/");
    }
}
