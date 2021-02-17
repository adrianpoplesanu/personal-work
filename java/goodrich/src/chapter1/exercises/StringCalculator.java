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
	
	public void removePunctuation(StringBuilder s) {
		String text = s.toString();
		text = text.replaceAll("\\p{Punct}", "");
		s.replace(0, s.length(), text);
	}
	
	public static void main(String[] args) {
		StringCalculator stringCalculator = new StringCalculator();
		System.out.println(stringCalculator.countVowels("buna dimineata!"));
		StringBuilder text = new StringBuilder("bu-na dimin,eata!");
		stringCalculator.removePunctuation(text);
		System.out.println(text);
	}
}
