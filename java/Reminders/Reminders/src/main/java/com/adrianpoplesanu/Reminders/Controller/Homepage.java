package com.adrianpoplesanu.Reminders.Controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class Homepage {
    @RequestMapping(value="/", method= RequestMethod.GET)
    @ResponseBody
    String index() {
        return "bebe dex e frumesh";
    }
}
