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
    public StatusModel status() {
        return new StatusModel(200,"Everything looks fine!");
    }

    @GetMapping("/check2")
    public StatusModel check2() {
        return new StatusModel(200,"Everything looks fine!");
    }

    @GetMapping("/test-view-old")
    public ModelAndView test_view(Model model, HttpServletRequest request) {
        return new ModelAndView(new PlainView());
    }

    @GetMapping("/test-user/{userId}")
    public User testUser(@PathVariable int userId) {
        User user = userService.getUser(userId);
        if (user != null) {
            return user;
        } else {
            return new User();
        }
    }

    @GetMapping("/test-all-users")
    public List<User> testAllUsers() {
        return userService.getUsers();
    }

    @PostMapping(value = "/test-add-user", consumes = MediaType.APPLICATION_JSON_VALUE)
    @ResponseBody
    public User testAddUser(@RequestBody User user) {
        //return "{\"status\": \"ok\"}";
        userService.addUser(user);
        return user;
    }

    @PutMapping(value = "/test-update-user", consumes = MediaType.APPLICATION_JSON_VALUE)
    @ResponseBody
    public User testUpdateUser(@RequestBody User user) {
        userService.updateUser(user);
        return user;
    }

    @DeleteMapping(value = "/test-delete-user/{userId}")
    public String testDeleteUser(@PathVariable int userId) {
        userService.deleteUser(userId);
        return "{\"status\": \"ok\"}";
    }
}
