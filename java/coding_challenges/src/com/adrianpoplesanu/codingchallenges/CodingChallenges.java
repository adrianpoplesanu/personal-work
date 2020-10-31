package com.adrianpoplesanu.codingchallenges;

public class CodingChallenges {

	public static void main(String[] args) {
		//System.out.println("running CodingChallenges...");
		TestWorldPayChallenge();
	}
	
	private static String checkOutput (String actual, String expected) {
		if (actual.equals(expected)) {
			return "Passed";
		}
		return "Failed";
	}
	
	private static void TestWorldPayChallenge () {
		WorldPayChallenge wpc = new WorldPayChallenge();
		String actual, expected;
		actual = wpc.Solve("There are no reoccuring phrases.");
		expected = "";
		System.out.println(checkOutput(actual, expected));
		
		actual = wpc.Solve("The quick brown fox is jumping over the fence");
		expected = "the";
		System.out.println(checkOutput(actual, expected));
		
		actual = wpc.Solve("The quick brown fox is jumping over the quick fence");
		expected = "the quick";
		System.out.println(checkOutput(actual, expected));
		
		actual = wpc.Solve("The quick brown fox. Is jumping over the quick brown fox is jumping over");
		expected = "the quick brown fox";
		System.out.println(checkOutput(actual, expected));
	}
}
