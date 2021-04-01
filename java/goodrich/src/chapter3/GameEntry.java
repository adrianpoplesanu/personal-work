package chapter3;

public class GameEntry {
	private String name;
	private int score;
	
	public GameEntry(String n, int s) {
		name = n;
		score = s;
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String n) {
		name = n;
	}
	
	public int getScore() {
		return score;
	}
	
	public void setScore(int s) {
		score = s;
	}
	
	public String toString() {
		return "(" + name + ", " + score + ")";
	}
}
