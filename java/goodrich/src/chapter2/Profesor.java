package chapter2;

public class Profesor {
	protected String name;
	protected int age;
	private int school_num;
	
	public Profesor(String name, int age) {
		this.name = name;
		this.age = age;
	}
	
	public Profesor(String name, int age, int school_num) {
		this.name = name;
		this.age = age;
		this.school_num = school_num;
	}
	
	public void Print() {
		System.out.println("Profesor[" + this.name + "; " + this.age + "; " + this.school_num + "]");
	}
}
