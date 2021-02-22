package chapter2;

public class CreditCard {
	private String accountNum;
	private String expDate;
	private String CVV;
	private String cardBrand;
	private String name;
	
	public CreditCard() {
		this.accountNum = null;
		this.expDate = null;
		this.CVV = null;
		this.cardBrand = null;
		this.name = null;
	}
	
	public CreditCard(String accountNum, String expDate, String cvv, String cardBrand, String name) {
		this.accountNum = accountNum;
		this.expDate = expDate;
		this.CVV = cvv;
		this.cardBrand = cardBrand;
		this.name = name;
	}
	
	public String getAccountNum() {
		return this.accountNum;
	}
	
	public void setAccountNum(String accountNum) {
		this.accountNum = accountNum;
	}

	public String getExpDate() {
		return this.expDate;
	}
	
	public void setExpDate(String expDate) {
		this.expDate = expDate;
	}
	
	public String getCVV() {
		return this.CVV;
	}
	
	public void setCVV(String cvv) {
		this.CVV = cvv;
	}

	public String getCardBrand() {
		return this.cardBrand;
	}
	
	public void setCardBrand(String cardBrand) {
		this.cardBrand = cardBrand;
	}

	public String getName() {
		return this.name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public static void main(String[] args) {

	}
}
