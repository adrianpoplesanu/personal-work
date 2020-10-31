package com.adrianpoplesanu.codingchallenges;

public class WorldPayChallenge {
	public String Solve(String text) {
		text = text.toLowerCase();
		String result = "";
		int totalWords = 0;
		
		String[] words = text.split("[ ]+");
		for (int i = 0; i < words.length; ++i) {
			String lookup = "";
			for (int j = i; j < words.length; ++j) {
				if (j == i) {
					lookup = words[j];
				} else {
					lookup = lookup + " " + words[j];
				}
				if (words[j].contains(".") || words[j].contains(",")) {
					// this is the last word of the phrase
					int firstOccurance = text.indexOf(lookup);
					int secondOccurance = text.indexOf(lookup, firstOccurance + 1);
					if (secondOccurance != -1) {
						if (j - i + 1 > totalWords) {
							result = lookup;
							totalWords = j - i + 1;
						}
					}
					break;
				} else {
					// no comma or dot so continue with adding words to lookup
					int firstOccurance = text.indexOf(lookup);
					int secondOccurance = text.indexOf(lookup, firstOccurance + 1);
					if (secondOccurance != -1) {
						if (j - i + 1 > totalWords) {
							result = lookup;
							totalWords = j - i + 1;
						}
					}
				}
			}
		}
		//System.out.println (result);
		return result;
	}
}
