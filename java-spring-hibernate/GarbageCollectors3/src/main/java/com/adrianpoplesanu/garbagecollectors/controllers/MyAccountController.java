package com.adrianpoplesanu.garbagecollectors.controllers;

import java.security.Principal;

import javax.servlet.http.HttpServletRequest;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.View;
import com.adrianpoplesanu.garbagecollectors.models.User;
import com.adrianpoplesanu.garbagecollectors.models.UserData;
import com.adrianpoplesanu.garbagecollectors.services.UserService;

@Controller
public class MyAccountController {
	@Autowired
	UserService userService;
	
	@RequestMapping(value="/myaccount", method=RequestMethod.POST)
	public String index(ModelMap model, Principal principal) {
		User user = userService.findByUsername (principal.getName());
		//UserData userData = userService.getUserData (user.getId()); // merge si asa
		UserData userData = user.getUserData(); // merge si asa
		model.addAttribute("message", "serverul spune: " + userData.toString());
		model.addAttribute("userData", userData);
		//model.addAttribute("user", user);
		return "myaccount";
	}
	
	@PostMapping("/update-account")
	public ModelAndView redirectPostToPost(HttpServletRequest request, 
			@ModelAttribute("UserData") UserData userData) {
		userService.updateUserData (userData);
	    request.setAttribute(View.RESPONSE_STATUS_ATTRIBUTE, HttpStatus.TEMPORARY_REDIRECT);
	    return new ModelAndView("redirect:/myaccount");
	}
}
