package com.adrianpoplesanu.garbagecollectors.services;

import java.util.List;

import com.adrianpoplesanu.garbagecollectors.models.User;
import com.adrianpoplesanu.garbagecollectors.models.UserData;

public interface UserService {
	public User findByUsernameJDBC(String username);
	public List<User> getAllUsers ();
	public UserData getUserDataJDBC(int userDataId);
	public void updateUserDataJDBC(UserData userData);
	
	public User findByUsername(String username);
	public UserData getUserData(int userDataId);
	public void updateUserData(UserData userData);
	public void insertUser(User user);
	public void deleteUser(int id);
	//public void insertUserData(UserData userData);
}
