package com.adrianpoplesanu.AnifScheduler.Controller;

import com.adrianpoplesanu.AnifScheduler.Model.Status.StatusModel;
import com.adrianpoplesanu.AnifScheduler.Model.User;
import com.adrianpoplesanu.AnifScheduler.Service.UserService;
import com.adrianpoplesanu.AnifScheduler.View.PlainView;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;
import java.util.List;

@RestController
public class StatusController {
    /*@GetMapping("/")
    String index() {
        return "Buna dimineata";
    }*/

    @Autowired
    UserService userService;

    @GetMapping("/status")
    StatusModel status() {
        return new StatusModel(200,"Everything looks fine!");
    }

    @GetMapping("/check2")
    StatusModel check2() {
        return new StatusModel(200,"Everything looks fine!");
    }

    @GetMapping("/test-view-old")
    ModelAndView test_view(Model model, HttpServletRequest request) {
        return new ModelAndView(new PlainView());
    }

    @GetMapping("/test-user/{userId}")
    User testUser(@PathVariable int userId) {
        User user = userService.getUser(userId);
        if (user != null) {
            return user;
        } else {
            return new User();
        }
    }

    @GetMapping("/test-all-users")
    List<User> testAllUsers() {
        return userService.getUsers();
    }

    @PostMapping(value = "/test-add-user", consumes = MediaType.APPLICATION_JSON_VALUE)
    @ResponseBody
    User testAddUser(@RequestBody User user) {
        //return "{\"status\": \"ok\"}";
        //userService.addUser(user);
        return user;
    }

    @PutMapping(value = "/test-update-user", consumes = MediaType.APPLICATION_JSON_VALUE)
    @ResponseBody
    User testUpdateUser(@RequestBody User user) {
        return user;
    }
}
