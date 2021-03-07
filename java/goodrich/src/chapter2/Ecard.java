package chapter2;

public class Ecard extends Product {
	private String storefront;
	
	/*public Ecard(String a) {
		super("aaa", 5, 4, 55, false); // fara o invocare super catre contructorul Product nu merge
	}*/

	public Ecard(String description, int price, int lowestPrice, int w, boolean hazardous, String storefront) {
		super(description, price, lowestPrice, w, hazardous);
		this.storefront = storefront;
	}
	
	public String getStorefront() {
		return storefront;
	}

	public static void main(String[] args) {
		Ecard c = new Ecard("Get well soon", 5, 3, 55, false, "bma");
		System.out.println(c.description());
		System.out.println(c.getStorefront());
	}
}
