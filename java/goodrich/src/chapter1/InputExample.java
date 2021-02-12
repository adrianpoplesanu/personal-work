package chapter1;

import java.util.Scanner;

public class InputExample {

	public static void main(String[] args) {
		System.out.println("Optimal weight calculator...");
		Scanner scanner = new Scanner(System.in);
		System.out.print("enter your age(years): ");
		double age = scanner.nextDouble();
		System.out.print("enter your height(cm): ");
		double height = scanner.nextDouble();
		scanner.close();
		System.out.println("your optimal wight is " + ((height - 100) + (age * 0.01f)));
	}
}
