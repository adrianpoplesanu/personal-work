package com.adrianpoplesanu.garbagecollectors.services;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.adrianpoplesanu.garbagecollectors.daos.UserDao;
import com.adrianpoplesanu.garbagecollectors.daos.UserDataDao;
import com.adrianpoplesanu.garbagecollectors.models.User;
import com.adrianpoplesanu.garbagecollectors.models.UserData;

@Service
public class UserServiceImpl implements UserService {

	@Autowired
	private UserDao userDao;
	
	@Autowired 
	private UserDataDao userDataDao;
	
	public User findByUsernameJDBC(String username) {
		return userDao.findByUsernameJDBC (username);
	}

	@Override
	public List<User> getAllUsers() {
		return userDao.getAllUsers(); // TODO return dao get all users.
	}

	@Override
	public UserData getUserDataJDBC(int userDataId) {
		return userDataDao.getUserDataJDBC (userDataId);
	}

	@Override
	public void updateUserDataJDBC(UserData userData) {
		userDataDao.updateUserDataJDBC (userData);
	}

	@Override
	public User findByUsername(String username) {
		return userDao.findByUsername (username);
	}

	@Override
	public UserData getUserData(int userDataId) {
		return userDataDao.getUserData (userDataId);
	}

	@Override
	public void updateUserData(UserData userData) {
		userDataDao.updateUserData (userData);
	}

	@Override
	public void insertUser(User user) {
		userDao.insertUser(user);
	}

	@Override
	public void deleteUser(int id) {
		userDao.deleteUser(id);
	}
}
