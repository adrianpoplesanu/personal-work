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

import com.adrianpoplesanu.garbagecollectors.models.User;
import com.adrianpoplesanu.garbagecollectors.models.UserData;
import com.adrianpoplesanu.garbagecollectors.models.UserRowMapper;

@Repository
@Transactional
public class UserDaoImpl implements UserDao {
	@Autowired
	private JdbcTemplate jdbcTemplate;
	
	@Autowired
	SessionFactory sessionFactory;

	@Override
	public User findByUsernameJDBC(String username) {
		String sql = "SELECT * FROM Users WHERE username = ?";
		 
		User user = (User)jdbcTemplate.queryForObject(
				sql, new Object[] { username }, new UserRowMapper());
		return user;
	}

	@Override
	public List<User> getAllUsers() {
		Session session = sessionFactory.openSession();
		Transaction tx = session.beginTransaction();
		List<User> users = session.createQuery("FROM User ORDER BY id").list();
		tx.commit();
		session.close();
		return users;
	}

	@Override
	public User findByUsername(String username) {
		Session session = sessionFactory.openSession();
		Transaction tx = session.beginTransaction();
		String hql = "FROM User WHERE username = :username";
		Query query = session.createQuery(hql);
		query.setParameter("username", username);
		List results = query.list();
		User user = (User)results.get(0);
		tx.commit();
		session.close();
		return user;
	}
	
	public void addUserRoles (int id, String username, String role) {
		String sql = "INSERT INTO user_roles values(%s, '%s', '%s')";
		jdbcTemplate.execute(String.format(sql, id, username, role));
	}

	@Override
	public void insertUser(User user) {
		Session session = sessionFactory.openSession();
		Transaction tx = session.beginTransaction();
		session.save(user);
		UserData userData = user.getUserData();
		userData.setId(user.getId());
		session.save(userData);
		tx.commit();
		session.close();
		addUserRoles(user.getId(), user.getUsername(), "ROLE_USER");
	}

	@Override
	public void deleteUser(int id) {
		String sql = "DELETE FROM user_roles WHERE user_role_id = %s";
		jdbcTemplate.execute(String.format(sql, id));
		sql = "DELETE FROM UserData WHERE id = %s";
		jdbcTemplate.execute(String.format(sql, id));
		sql = "DELETE FROM Users WHERE id = %s";
		jdbcTemplate.execute(String.format(sql, id));
	}
}
