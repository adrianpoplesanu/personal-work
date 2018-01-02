package com.adrianpoplesanu.garbagecollectors.controllers;

import java.security.Principal;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

import com.adrianpoplesanu.garbagecollectors.models.User;
import com.adrianpoplesanu.garbagecollectors.models.UserData;
import com.adrianpoplesanu.garbagecollectors.services.UserService;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

@Controller
public class AdminController {
	@Autowired
	UserService userService;
	
	@RequestMapping(value="/admin/users", method=RequestMethod.GET)
	public String index(ModelMap model, Principal principal) {
		ObjectMapper mapper = new ObjectMapper();
		List<User> users = userService.getAllUsers();
		try {
			model.addAttribute("users", mapper.writeValueAsString(users));
		} catch (JsonProcessingException e) {
			model.addAttribute("users", "error mapping JSON");
			e.printStackTrace();
		}
		//model.addAttribute("users", users);
		return "admin/users";
	}
	
	@RequestMapping(value="/admin/users/json", method=RequestMethod.GET)
	@ResponseBody
	public String getAllUsers() {
		ObjectMapper mapper = new ObjectMapper();
		List<User> users = userService.getAllUsers();
		String output = "";
		try {
			output = "{\"data\": " + mapper.writeValueAsString(users) + "}";
		} catch (JsonProcessingException e) {
			output = "error mapping JSON";
			e.printStackTrace();
		}
		return output;
	}
	
	@RequestMapping(value="/admin/users/add", method=RequestMethod.POST)
	@ResponseBody
	public String add(Principal principal,
			@RequestParam("username") String username,
			@RequestParam("password") String password,
			@RequestParam("name") String name,
			@RequestParam("contact") String contact,
			@RequestParam("email") String email,
			@RequestParam("address") String address,
			@RequestParam("telefon") String telefon,
			@RequestParam("oras") String oras,
			@RequestParam("judet") String judet,
			@RequestParam("zipCode") String zipCode,
			@RequestParam("website") String website,
			@RequestParam("description") String description,			
			@RequestParam("jnumber") String jNumber,
			@RequestParam("tip") String tip,
			@RequestParam("cui") String cui,
			@RequestParam("autorizatie_mediu") String autorizatieMediu) {
		// this works... it's all i need
		ObjectMapper mapper = new ObjectMapper();
		User user = new User();
		UserData userData = new UserData();
		user.setUsername(username);
		user.setPassword(password);
		user.setEnabled(1);
		userData.setName(name);
		userData.setContact(contact);
		userData.setEmail(email);
		userData.setAddress(address);
		userData.setTelefon(telefon);
		userData.setOras(oras);
		userData.setJudet(judet);
		userData.setZipCode(zipCode);
		userData.setWebsite(website);
		userData.setDescription(description);
		userData.setjNumber(jNumber);
		userData.setTip(tip);
		userData.setCui(cui);
		userData.setAutorizatieMediu(autorizatieMediu);
		user.setUserData(userData);
		userData.setUser(user);
		userService.insertUser(user);
		String output = "";
		try {
			output = mapper.writeValueAsString(user);
		} catch (JsonProcessingException e) {
			output = "error mapping JSON";
			e.printStackTrace();
		}
		return output;
	}
	
	@RequestMapping(value="/admin/users/edit", method=RequestMethod.POST)
	@ResponseBody
	public String edit(Principal principal,
			@RequestParam("id") int id,
			@RequestParam("name") String name,
			@RequestParam("contact") String contact,
			@RequestParam("email") String email,
			@RequestParam("address") String address,
			@RequestParam("telefon") String telefon,
			@RequestParam("oras") String oras,
			@RequestParam("judet") String judet,
			@RequestParam("zipCode") String zipCode,
			@RequestParam("website") String website,
			@RequestParam("description") String description,			
			@RequestParam("jnumber") String jNumber,
			@RequestParam("tip") String tip,
			@RequestParam("cui") String cui,
			@RequestParam("autorizatie_mediu") String autorizatieMediu) {
		// this works... it's all i need
		ObjectMapper mapper = new ObjectMapper();
		UserData userData = new UserData();
		userData.setId(id);
		userData.setName(name);
		userData.setContact(contact);
		userData.setEmail(email);
		userData.setAddress(address);
		userData.setTelefon(telefon);
		userData.setOras(oras);
		userData.setJudet(judet);
		userData.setZipCode(zipCode);
		userData.setWebsite(website);
		userData.setDescription(description);
		userData.setjNumber(jNumber);
		userData.setTip(tip);
		userData.setCui(cui);
		userData.setAutorizatieMediu(autorizatieMediu);
		userService.updateUserData(userData);
		String output = "";
		try {
			output = mapper.writeValueAsString(userData);
		} catch (JsonProcessingException e) {
			output = "error mapping JSON";
			e.printStackTrace();
		}
		return output;
	}
	
	@RequestMapping(value="/admin/users/delete", method=RequestMethod.POST)
	@ResponseBody
	public String delete(Principal principal,
			@RequestParam("id") int id) {
		userService.deleteUser(id);
		return "success";
	}
}
