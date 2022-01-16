package com.adrianpoplesanu.SudokuWebSolver.Controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping(value = "/")
public class HomepageController {
    @RequestMapping(method = RequestMethod.GET)
    @ResponseBody
    public String index() {
        return "buna dimineata!";
    }
}
