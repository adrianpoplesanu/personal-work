package requests;

import java.io.IOException;
import java.net.MalformedURLException;
import java.util.Map;

public interface RequestLibrary {
	String get(String url) throws MalformedURLException, IOException;
	String post(String url);
	String get(String url, Map<String, String> queryParameters);
	String post(String url, Map<String, String> payloadParameters);
	
	String get(String url, Map<String, String> headers, Map<String, String> queryParameters, boolean checkCertificates) throws IOException;
}
