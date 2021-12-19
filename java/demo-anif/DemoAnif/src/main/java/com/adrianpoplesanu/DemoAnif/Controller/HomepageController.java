package com.adrianpoplesanu.DemoAnif.Controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.servlet.ModelAndView;

@Controller
public class HomepageController {
    @RequestMapping(value = "/")
    @GetMapping
    @ResponseBody
    String index() {
        //ModelAndView model = new ModelAndView();
        //model.setViewName("homepage");
        //return model;
        return "buna dimineata!";
    }

    @GetMapping(value="/test")
    @ResponseBody
    String test() {
        return "test-page";
    }

    @GetMapping(value="/test2")
    ModelAndView test2() {
        ModelAndView model = new ModelAndView();
        model.setViewName("homepage");
        return model;
    }
}
