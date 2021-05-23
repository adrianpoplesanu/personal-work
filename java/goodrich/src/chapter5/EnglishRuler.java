package chapter5;

public class EnglishRuler {
	
	public static void drawRuler(int nInches, int majorLength) {
		drawLine(majorLength, 0);
		for (int i = 0; i < nInches; i++) {
			drawInterval(majorLength - 1);
			drawLine(majorLength, i + 1);
		}
	}
	
	public static void drawInterval(int centralLength) {
		if (centralLength > 0) {
			drawInterval(centralLength - 1);
			drawLine(centralLength);
			drawInterval(centralLength - 1);
		}
	}
	
	public static void drawLine(int tickLength, int label) {
		for (int i = 0; i < tickLength; i++) System.out.print("-");
		if (label >= 0) {
			System.out.print(" ");
			System.out.print(label);
		}
		System.out.print("\n");
	}
	
	public static void drawLine(int tickLength) {
		drawLine(tickLength, -1);
	}

	public static void main(String[] args) {
		System.out.println("running EnglishRuler...");
		drawRuler(3, 3);
	}
}
