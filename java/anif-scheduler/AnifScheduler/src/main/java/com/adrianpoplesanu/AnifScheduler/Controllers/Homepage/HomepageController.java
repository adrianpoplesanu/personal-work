package com.adrianpoplesanu.AnifScheduler.Controllers.Homepage;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

@Controller
@RequestMapping(value = "/")
public class HomepageController {
    @GetMapping
    ModelAndView index() {
        ModelAndView mv = new ModelAndView();
        mv.setViewName("homepage");
        mv.getModel().put("data", "Welcome home man");
        return mv;
    }
}
