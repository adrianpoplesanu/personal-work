package com.adrianpoplesanu.garbagecollectors.controllers;

import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller
@RequestMapping(value="/hello")
public class LoginController {
	@RequestMapping(value="/index", method=RequestMethod.GET)
	public String index(ModelMap model) {
		model.addAttribute("message", "vine din controller");
		return "login";
	}
}
