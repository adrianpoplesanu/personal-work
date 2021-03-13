package chapter2;

public class ProfesorTest {
	public static void main(String[] args) {
		Profesor profesor1 = new ProfesorUniversitar("Tavi Stanashel", 190, 3);
		profesor1.Print();
		ProfesorUniversitar profesor_universitar1 = (ProfesorUniversitar) profesor1;
		profesor_universitar1.Print();
		Profesor profesor2 = new Profesor("Tavitz Stanashit", 1000, 7);
		profesor2.Print();
	}
}
