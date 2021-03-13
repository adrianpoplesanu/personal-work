package chapter2;

public class ProfesorUniversitar extends Profesor {
	private int university_num;
	
	public ProfesorUniversitar(String name, int age, int university_num) {
		super(name, age);
		this.university_num = university_num;
	}

	public void Print() {
		System.out.println("ProfesorUniversitar[" + this.name + "; " + this.age + "; " + this.university_num + "]");
	}
}
