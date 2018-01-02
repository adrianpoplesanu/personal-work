package com.adrianpoplesanu.garbagecollectors.models;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.OneToOne;
import javax.persistence.PrimaryKeyJoinColumn;
import javax.persistence.Table;

import org.hibernate.annotations.GenericGenerator;
import org.hibernate.annotations.Parameter;

import com.fasterxml.jackson.annotation.JsonBackReference;

@Entity
@Table(name="UserData")
public class UserData implements Serializable {
	private static final long serialVersionUID = 1L;
	
	//@GenericGenerator(name = "generator", strategy = "foreign", 
	//		parameters = @Parameter(name = "property", value = "id"))
	@Id
	//@GeneratedValue(generator = "generator")
	@Column(name="id")
	private int id;
	@Column(name="name")
	private String name;
	@Column(name="address")
	private String address;
	@Column(name="jnumber")
	private String jNumber;
	@Column(name="tip")
	private String tip;
	@Column(name="autorizatie_mediu")
	private String autorizatieMediu;
	@Column(name="persoana_contact")
	private String contact;
	@Column(name="email")
	private String email;
	@Column(name="telefon")
	private String telefon;
	@Column(name="oras")
	private String oras;
	@Column(name="cod_postal")
	private String zipCode;
	@Column(name="description")
	private String description;
	@Column(name="cui")
	private String cui;
	@Column(name="judet")
	private String judet;
	@Column(name="website")
	private String website;
	
	@OneToOne
	@JoinColumn(name="id", referencedColumnName="id")
	@JsonBackReference
	private User user;
	
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getAddress() {
		return address;
	}
	public void setAddress(String address) {
		this.address = address;
	}
	public String getTip() {
		return tip;
	}
	public void setTip(String tip) {
		this.tip = tip;
	}
	public String getjNumber() {
		return jNumber;
	}
	public void setjNumber(String jNumber) {
		this.jNumber = jNumber;
	}	
	public String getAutorizatieMediu() {
		return autorizatieMediu;
	}
	public void setAutorizatieMediu(String autorizatieMediu) {
		this.autorizatieMediu = autorizatieMediu;
	}	
	public String getContact() {
		return contact;
	}
	public void setContact(String contact) {
		this.contact = contact;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	public String getTelefon() {
		return telefon;
	}
	public void setTelefon(String telefon) {
		this.telefon = telefon;
	}
	public String getOras() {
		return oras;
	}
	public void setOras(String oras) {
		this.oras = oras;
	}
	public String getZipCode() {
		return zipCode;
	}
	public void setZipCode(String zipCode) {
		this.zipCode = zipCode;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		this.description = description;
	}
	public String getCui() {
		return cui;
	}
	public void setCui(String cui) {
		this.cui = cui;
	}
	public String getJudet() {
		return judet;
	}
	public void setJudet(String judet) {
		this.judet = judet;
	}
	public String getWebsite() {
		return website;
	}
	public void setWebsite(String website) {
		this.website = website;
	}
	
	public User getUser() {
		return this.user;
	}

	public void setUser(User user) {
		this.user = user;
	}
	
	@Override
	public String toString() {
		return "UserData[ " + id + " , " + name + " , " + address + " , " + jNumber + " , " + tip + " , " + autorizatieMediu  + " , " + user.getUsername() + " , " + user.getId()  + " ]";
	}
}
