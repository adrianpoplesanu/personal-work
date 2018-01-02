package com.adrianpoplesanu.garbagecollectors.controllers;

import java.security.Principal;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import com.adrianpoplesanu.garbagecollectors.models.User;
import com.adrianpoplesanu.garbagecollectors.services.UserService;

@Controller
public class HomepageController {
	@Autowired
	UserService userService;
	
	@RequestMapping(value={"/"}, method=RequestMethod.GET)
	public String index(ModelMap model, Principal principal) {
		//User user = userService.findByUsernameJDBC(principal.getName());
		User user = userService.findByUsername(principal.getName());
		model.addAttribute("message", "serverul spune: " + user.toString()); // TODO remove this
		return "home";
	}
}
