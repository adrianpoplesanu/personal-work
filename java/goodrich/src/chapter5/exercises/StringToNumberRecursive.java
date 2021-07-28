package chapter5.exercises;

public class StringToNumberRecursive {

	public static int convertStringToIntRecursive(String text) {
		if (text.length() == 0) {
			return 0;
		} else {
			int digit = Character.getNumericValue(text.charAt(text.length() - 1));
		    return (convertStringToIntRecursive(text.substring(0, text.length() - 1)) * 10) + digit;	
		}
	}
	
	public static void main(String[] args) {
		System.out.println(convertStringToIntRecursive("12569") + 22);
	}
}
