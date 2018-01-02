package com.adrianpoplesanu.garbagecollectors.daos;

import java.util.List;

import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

import com.adrianpoplesanu.garbagecollectors.models.UserData;
import com.adrianpoplesanu.garbagecollectors.models.UserDataRowMapper;

@Repository
@Transactional
public class UserDataDaoImpl implements UserDataDao {
	@Autowired
	private JdbcTemplate jdbcTemplate;
	
	@Autowired 
	private SessionFactory sessionFactory;
	
	@Override
	public UserData getUserDataJDBC (int userDataId) {
		String sql = "SELECT * FROM UserData WHERE id = ?";
		UserData userData = (UserData)jdbcTemplate.queryForObject(sql, 
				new Object[] {userDataId}, new UserDataRowMapper ());
		return userData;
	}

	@Override
	public UserData getAllUserData() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void addUserData() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void updateUserDataJDBC (UserData userData) {
		String sql = "UPDATE UserData SET name= ?, address = ?, jnumber = ?, tip = ?, autorizatie_mediu = ?, "
				+ "cui = ?, description = ?, persoana_contact = ?, email = ?, telefon = ?, oras = ?, "
				+ "judet = ?, cod_postal = ?, website = ? WHERE id = ?"; // de aia era frumos cu hybernate, e ok si asa though
		jdbcTemplate.update(sql, new Object[] {
				userData.getName(),
				userData.getAddress(), 
				userData.getjNumber(), 
				userData.getTip(),
				userData.getAutorizatieMediu(), 
				userData.getCui(), 
				userData.getDescription(), 
				userData.getContact(),
				userData.getEmail(), 
				userData.getTelefon(), 
				userData.getOras(), 
				userData.getJudet(),
				userData.getZipCode(),
				userData.getWebsite(),
				userData.getId()});
	}

	@Override
	public UserData getUserData (int userDataId) {
		Session session = sessionFactory.openSession();
		Transaction tx = session.beginTransaction();
		String hql = "FROM UserData WHERE id = :userDataId";
		Query query = session.createQuery(hql);
		query.setParameter("userDataId", userDataId);
		List results = query.list();
		UserData userData = (UserData) results.get(0);
		tx.commit();
		session.close();
		return userData;
	}

	@Override
	public void updateUserData (UserData userData) {
		// TODO Auto-generated method stub
		Session session = sessionFactory.openSession();
		Transaction tx = session.beginTransaction();
		session.update(userData);
		tx.commit();
		session.close();
	}

}
