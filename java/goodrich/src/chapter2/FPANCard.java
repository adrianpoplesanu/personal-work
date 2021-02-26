package chapter2;

public class FPANCard extends CreditCard {
	private float chargeRate;
	
	public FPANCard() {
		super();
		this.chargeRate = 0f;
	}
	
	public FPANCard(String accountNum, String expDate, String cvv, String cardBrand, 
				String name, float balance, float limit, float chargeRate) {
		super(accountNum, expDate, cvv, cardBrand, name, balance, limit);
		this.chargeRate = chargeRate;
	}
	
	public void processMonth() {
		this.balance -= this.balance * 0.02; // each month you lose 2%
	}
	
	public boolean charge(float amount) {
		boolean isSuccess = super.charge(amount);
		if (isSuccess) this.balance -= chargeRate * amount; // remove a charge rate
		return isSuccess;
	}
	
	public float getChargeRate() {
		return this.chargeRate;
	}
	
	public void setChargeRate(float chargeRate) {
		this.chargeRate = chargeRate;
	}
	
	public static void main(String[] args) {
		CreditCard cc1 = new CreditCard();
		FPANCard fpan1 = new FPANCard();
		
		CreditCard cc2 = new CreditCard("4444444444444448", "02/23", "123", "VI", 
				"ADRIANUS ADRIANUS", 100f, 1000f);
		FPANCard fpan2 = new FPANCard("5454545454545454", "08/24", "234", "MC",
				"ADRIANUS ADRIANUS", 200f, 1500f, 0.02f);
	}
}
