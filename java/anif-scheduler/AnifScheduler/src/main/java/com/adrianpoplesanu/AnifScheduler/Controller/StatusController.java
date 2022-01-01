package com.adrianpoplesanu.AnifScheduler.Controller;

import com.adrianpoplesanu.AnifScheduler.Model.Status.StatusModel;
import com.adrianpoplesanu.AnifScheduler.View.PlainView;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;

@RestController
public class StatusController {
    /*@GetMapping("/")
    String index() {
        return "Buna dimineata";
    }*/

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
}
