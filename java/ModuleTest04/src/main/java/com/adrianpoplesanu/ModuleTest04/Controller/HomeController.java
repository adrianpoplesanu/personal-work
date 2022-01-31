package com.adrianpoplesanu.ModuleTest04.Controller;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class HomeController {
    @RequestMapping(value = "/", method = RequestMethod.GET)
    @ResponseBody
    public String index(@Value("${text}") String text) {
        return text;
    }
}
