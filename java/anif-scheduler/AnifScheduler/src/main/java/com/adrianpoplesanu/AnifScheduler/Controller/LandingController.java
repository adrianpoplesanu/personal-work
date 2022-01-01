package com.adrianpoplesanu.AnifScheduler.Controller;

import com.adrianpoplesanu.AnifScheduler.View.PlainView;
import org.springframework.http.MediaType;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;

@Controller
public class LandingController {
    @GetMapping("/test-view")
    ModelAndView test_view(Model model, HttpServletRequest request) {
        return new ModelAndView(new PlainView());
    }

    @GetMapping(value = "/test-view2", produces = MediaType.TEXT_HTML_VALUE)
    @ResponseBody
    String test_view2(Model model, HttpServletRequest request) {
        return "<html><h1>Buna dimineata!</h1></html>";
    }
}
