package chapter2;

public class CreditCard {
	private String accountNum;
	private String expDate;
	private String CVV;
	private String cardBrand;
	private String name;
	protected float balance;
	private float limit;
	
	public CreditCard() {
		this.accountNum = null;
		this.expDate = null;
		this.CVV = null;
		this.cardBrand = null;
		this.name = null;
		this.balance = 0f;
		this.limit = 0f;
	}
	
	public CreditCard(String accountNum, String expDate, String cvv, String cardBrand, 
					  String name, float balance, float limit) {
		this.accountNum = accountNum;
		this.expDate = expDate;
		this.CVV = cvv;
		this.cardBrand = cardBrand;
		this.name = name;
		this.balance = balance;
		this.limit = limit;
	}
	
	public boolean charge(float amount) {
		if (this.balance + amount < this.limit) {
			this.balance += amount;
			return true;
		}
		return false;
	}
	
	public void makePayment(float amount)  {
		this.balance -= amount;
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
	
	public float getBalance() {
		return this.balance;
	}
	
	public void setBalance(float balance) {
		this.balance = balance;
	}
	
	public float getLimit() {
		return this.limit;
	}
	
	public void setLimit(float limit) {
		this.limit = limit;
	}
}
