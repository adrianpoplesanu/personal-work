package chapter3;

public class CaesarCipher {
	private char[] encoder = new char[26];
	private char[] decoder = new char[26];
	
	public CaesarCipher(int displacement) {
		while(displacement > 26) displacement -= 26;
		while(displacement < 0) displacement += 26;
		for (int i = 0; i < 26; i++) {
			encoder[i] = (char) ('A' + ((i + displacement) % 26));
			decoder[i] = (char) ('A' + ((i - displacement + 26) % 26));
		}
	}
	
	public String encode(String msg) {
		System.out.println("encoding with: " + String.valueOf(encoder));
		return transform(msg, encoder);
	}
	
	public String decode(String msg) {
		System.out.println("decoding with: " + String.valueOf(decoder));
		return transform(msg, decoder);
	}
	
	private String transform(String msg, char[] cipher) {
		char[] original = msg.toCharArray();
		char[] output = original;
		for (int i = 0; i < original.length; i++) {
			if (Character.isUpperCase(original[i])) {
				output[i] = cipher[original[i] - 'A'];
			}
		}
		return String.valueOf(output);
	}
	
	public static void main(String[] args) {
		CaesarCipher cipher = new CaesarCipher(-100);
		String coded = cipher.encode("BUNA DIMINEATA!");
		System.out.println(coded);
		String decoded = cipher.decode(coded);
		System.out.println(decoded);
	}
}
