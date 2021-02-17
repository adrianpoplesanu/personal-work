package chapter1.exercises;

public class StringCalculator {

	public int countVowels(String s) {
		int count = 0;
		for (int i = 0; i < s.length(); ++i) {
			if (s.charAt(i) == 'a' || 
				s.charAt(i) == 'e' || 
				s.charAt(i) == 'i' ||
				s.charAt(i) == 'o' ||
				s.charAt(i) == 'u') count++;
		}
		return count;
	}
	
	public static void main(String[] args) {
		StringCalculator stringCalculator = new StringCalculator();
		System.out.println(stringCalculator.countVowels("buna dimineata!"));
	}
}
