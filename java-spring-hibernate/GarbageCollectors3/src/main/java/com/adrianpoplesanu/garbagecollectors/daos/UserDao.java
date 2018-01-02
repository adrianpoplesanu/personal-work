package com.adrianpoplesanu.garbagecollectors.daos;

import java.util.List;

import com.adrianpoplesanu.garbagecollectors.models.User;

public interface UserDao {
	public User findByUsernameJDBC(String username);
	
	public List<User> getAllUsers ();
	public User findByUsername(String username);
	public void insertUser(User user);

	public void deleteUser(int id);
}
