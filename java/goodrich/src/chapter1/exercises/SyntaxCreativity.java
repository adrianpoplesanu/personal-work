package chapter1.exercises;

public class SyntaxCreativity {
	
	public void carbon() {
		int i = 0;
		char[] letter = {'c', 'a', 'r', 'b', 'o', 'n'};
		while (i < Math.pow(2, 6)) {
			String binary_representation = Integer.toBinaryString(i);
			for (int j = 0; j < binary_representation.length(); ++j) {
				if (binary_representation.charAt(j) == '1') System.out.print(letter[j]);
			}
			System.out.print('\n');
			i++;
		}
		//System.out.println(Integer.toBinaryString(i));
	}
	
	public void carbon(String text) {
		
	}

	public static void main(String[] args) {
		SyntaxCreativity syntaxCreativity = new SyntaxCreativity();
		syntaxCreativity.carbon();
		syntaxCreativity.carbon("carbon");
	}
}
