package chapter3;

public class Scoreboard {
	private int numEntries = 0;
	private GameEntry[] board;
	
	public Scoreboard(int capacity) {
		board = new GameEntry[capacity];
	}
	
	public void addScore(GameEntry e) {
		int currentScore = e.getScore();
		if (numEntries < board.length || currentScore > board[numEntries - 1].getScore()) {
			if (numEntries < board.length) {
				numEntries++;
			}
			int j = numEntries - 1;
			while (j > 0 && currentScore > board[j - 1].getScore()) {
				board[j] = board[j - 1];
				j--;
			}
			board[j] = e;
		}
	}
	
	public GameEntry removeScore(int k) {
		GameEntry temp = board[k];
		while (k < numEntries - 1) {
			board[k] = board[k + 1];
			k++;
		}
		board[k] = null;
		numEntries--;
		return temp;
	}
	
	public void Show() {
		for (int i = 0; i < numEntries; i++) System.out.println(board[i].getName() + " " + board[i].getScore());
	}
	
	public static void main(String[] args) {
		System.out.println("in the shadow of the big bear");
		Scoreboard s = new Scoreboard(4);
		s.addScore(new GameEntry("dexiciut", 100));
		s.addScore(new GameEntry("ramunesh", 400));
		s.addScore(new GameEntry("adrish", 10));
		s.addScore(new GameEntry("harry poter", 50));
		s.addScore(new GameEntry("longbottom", 4));
		s.Show();
		s.addScore(new GameEntry("hermione", 50));
		s.Show();
		s.removeScore(3);
		s.removeScore(2);
		s.Show();
	}
}
