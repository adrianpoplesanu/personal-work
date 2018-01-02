package com.adrianpoplesanu.garbagecollectors.controllers;

import javax.servlet.http.HttpServletRequest;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;

@Controller
public class ErrorsController {
	@RequestMapping(value="/errors", method={RequestMethod.GET, RequestMethod.POST})
	public ModelAndView index(HttpServletRequest httpRequest) {
		ModelAndView errorPage = new ModelAndView("error");
		errorPage.addObject("code", getErrorCode(httpRequest));
		errorPage.addObject("exception", getErrorMessage(httpRequest));
		return errorPage;
	}
	
    private int getErrorCode(HttpServletRequest httpRequest) {
        return (Integer) httpRequest
          .getAttribute("javax.servlet.error.status_code");
    }
    
    private String getErrorMessage(HttpServletRequest httpRequest) {
        return (String) httpRequest
          .getAttribute("javax.servlet.error.exception");
    }
}
