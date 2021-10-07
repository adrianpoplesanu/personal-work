package requests;

import java.io.IOException;
import java.net.MalformedURLException;
import java.util.HashMap;
import java.util.Map;

public class RequestLibraryApplication {
	
	public static void getGoogleHomepage() throws MalformedURLException, IOException {
		RequestLibrary requests = new RequestLibraryImpl();
		String response;
		response = requests.get("https://www.google.com");
		System.out.println(response);		
	}
	
	private static Map<String, String> getHeaders() {
		Map<String, String> headers = new HashMap<String, String>();
		headers.put("X-Auth-Token", "f5c1f45ccb174b739541ad43203c7183");
		return headers;
		
	}
	
	public static void getLiveScores() throws IOException {
		RequestLibrary requests = new RequestLibraryImpl();
		String response;
		Map<String, String> headers = getHeaders();
		Map<String, String> queryParams = new HashMap<String, String>();
		response = requests.get("https://api.football-data.org/v2/competitions/EC/matches", headers, queryParams, false);
		System.out.println(response);
		//response = requests.get("https://api.football-data.org/v2/competitions/EC/matches", headers, queryParams, true);
		// this fails because of the old hack that i implemented
		//System.out.println(response);
		//response = requests.get("https://api.football-data.org/v2/competitions/EC/matches", headers, queryParams, false);
		//System.out.println(response);
	}

	public static void main(String[] args) {
		try {
			getGoogleHomepage();
		} catch (IOException e) {
			e.printStackTrace();
		}
		try {
			getLiveScores();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
