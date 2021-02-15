package chapter1.exercises;

public class GameEntry {
	public int score = 0;
	
	public GameEntry() {
		score = 0;
	}
	
	public static void main(String[] args) {
		GameEntry[] a = new GameEntry[7];
		GameEntry[] b;
		a[4] = new GameEntry();
		b = a.clone();
		a[4].score = 550;
		System.out.println(b[4].score);
		b[4].score++;
		System.out.println(a[4].score);
	}
}
