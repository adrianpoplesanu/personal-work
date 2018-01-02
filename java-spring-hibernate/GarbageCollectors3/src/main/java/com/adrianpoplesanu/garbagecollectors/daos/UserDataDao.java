package com.adrianpoplesanu.garbagecollectors.daos;

import com.adrianpoplesanu.garbagecollectors.models.UserData;

public interface UserDataDao {
	public UserData getUserDataJDBC (int userDataId);
	public UserData getAllUserData ();
	public void addUserData();
	public void updateUserDataJDBC (UserData userData);
	
	public UserData getUserData (int userDataId);
	public void updateUserData (UserData userData);
}
