package requests;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.security.KeyManagementException;
import java.security.NoSuchAlgorithmException;
import java.util.Map;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSocketFactory;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

public class RequestLibraryImpl implements RequestLibrary {

	private HttpURLConnection connect(String targetURL) throws IOException {
		URL url = new URL(targetURL);
		HttpURLConnection con = (HttpURLConnection) url.openConnection();
		return con;
	}
	
	private HttpsURLConnection connectSecure(String targetURL) throws IOException {
		URL url = new URL(targetURL);
		HttpsURLConnection con = (HttpsURLConnection) url.openConnection();
		return con;
	}
	
	private String readResponseText(HttpURLConnection con) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
		String inputLine;
		StringBuffer content = new StringBuffer();
		while((inputLine = in.readLine()) != null) {
			content.append(inputLine);
		}
		return content.toString();
	}
	
	TrustManager[] trustAllCerts = new TrustManager[]{
	        new X509TrustManager() {

	            public java.security.cert.X509Certificate[] getAcceptedIssuers()
	            {
	                return null;
	            }
	            public void checkClientTrusted(java.security.cert.X509Certificate[] certs, String authType)
	            {
	                //No need to implement.
	            }
	            public void checkServerTrusted(java.security.cert.X509Certificate[] certs, String authType)
	            {
	                //No need to implement.
	            }
	        }
	};

	
	@Override
	public String get(String url) throws IOException {
		HttpURLConnection con = connect(url);
		con.setRequestMethod("GET");
		String response = readResponseText(con);
		return response;
	}

	@Override
	public String post(String url) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String get(String url, Map<String, String> queryParameters) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String post(String url, Map<String, String> payloadParameters) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String get(String url, Map<String, String> headers, Map<String, String> queryParameters, boolean checkCertificates) throws IOException {
		SSLSocketFactory old = HttpsURLConnection.getDefaultSSLSocketFactory();
		if (!checkCertificates) {
			SSLContext sc;
			try {
				sc = SSLContext.getInstance("SSL");
			    sc.init(null, trustAllCerts, new java.security.SecureRandom());
			    HttpsURLConnection.setDefaultSSLSocketFactory(sc.getSocketFactory());
			} catch (NoSuchAlgorithmException | KeyManagementException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		HttpsURLConnection con = (HttpsURLConnection) connectSecure(url);
		con.setRequestMethod("GET");
		for(Map.Entry<String, String> entry : headers.entrySet()) {
			con.setRequestProperty(entry.getKey(), entry.getValue());
		}
		String response = readResponseText(con);
		HttpsURLConnection.setDefaultSSLSocketFactory(old);
		return response;
	}
}
