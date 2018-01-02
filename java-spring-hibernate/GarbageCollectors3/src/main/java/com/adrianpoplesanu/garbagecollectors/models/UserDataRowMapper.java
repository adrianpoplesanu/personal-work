package com.adrianpoplesanu.garbagecollectors.models;

import java.sql.ResultSet;
import java.sql.SQLException;

import org.springframework.jdbc.core.RowMapper;

public class UserDataRowMapper implements RowMapper {
	@Override
	public Object mapRow(ResultSet rs, int rowNum) throws SQLException {
		UserData userData = new UserData();
		userData.setId(rs.getInt("id"));
		userData.setName(rs.getString("name"));
		userData.setAddress(rs.getString("address"));
		userData.setjNumber(rs.getString("jNumber"));
		userData.setTip(rs.getString("tip"));
		userData.setAutorizatieMediu(rs.getString("autorizatie_mediu"));
		userData.setContact(rs.getString("persoana_contact"));
		userData.setEmail(rs.getString("email"));
		userData.setTelefon(rs.getString("telefon"));
		userData.setOras(rs.getString("oras"));
		userData.setZipCode(rs.getString("cod_postal"));
		userData.setDescription(rs.getString("description"));
		userData.setCui(rs.getString("cui"));
		userData.setJudet(rs.getString("judet"));
		userData.setWebsite(rs.getString("website"));
		
		return userData;
	}
}