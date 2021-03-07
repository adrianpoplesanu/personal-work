package chapter2;

public class Product implements Sellable, Transportable {
	private int price;
	private int lowestPrice;
	private String description;
	private boolean hazardous;
	private int w;
	
	public Product(String description, int price, int lowestPrice, int w, boolean hazardous) {
		this.description = description;
		this.price = price;
		this.lowestPrice = lowestPrice;
		this.w = w;
		this.hazardous = hazardous;
	}

	@Override
	public int weight() {
		// TODO Auto-generated method stub
		return w;
	}

	@Override
	public boolean isHazardous() {
		// TODO Auto-generated method stub
		return hazardous;
	}

	@Override
	public String description() {
		// TODO Auto-generated method stub
		return description;
	}

	@Override
	public int listPrice() {
		// TODO Auto-generated method stub
		return price;
	}

	@Override
	public int limitPrice() {
		// TODO Auto-generated method stub
		return lowestPrice;
	}

}
