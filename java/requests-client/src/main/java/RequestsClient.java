import javax.net.ssl.*;
import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.security.KeyManagementException;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.Map;
import java.util.StringJoiner;

public class RequestsClient {

    TrustManager[] trustAllCerts = new TrustManager[]{
        new X509TrustManager() {
            public java.security.cert.X509Certificate[] getAcceptedIssuers() {
                return null;
            }

            public void checkClientTrusted(java.security.cert.X509Certificate[] certs, String authType) {
                //No need to implement.
            }

            public void checkServerTrusted(java.security.cert.X509Certificate[] certs, String authType) {
                //No need to implement.
            }
        }
    };

    public String get(String path) throws IOException {
        URL url = new URL(path);
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");

        BufferedReader in = new BufferedReader(
                new InputStreamReader(con.getInputStream()));
        String inputLine;
        StringBuffer content = new StringBuffer();
        while ((inputLine = in.readLine()) != null) {
            content.append(inputLine);
        }
        in.close();
        return content.toString();
    }

    public String post(String path, Map<String, String> headers, Map<String, String> params) throws IOException {
        URL url = new URL("https://httpbin.org/post");
        URLConnection con = url.openConnection();
        HttpURLConnection http = (HttpURLConnection)con;
        http.setRequestMethod("POST"); // PUT is another valid option
        http.setDoOutput(true);

        Map<String,String> arguments = new HashMap<String, String>();
        arguments.put("username", "root");
        arguments.put("password", "sjh76HSn!"); // This is a fake password obviously
        StringJoiner sj = new StringJoiner("&");
        for(Map.Entry<String,String> entry : arguments.entrySet())
            sj.add(URLEncoder.encode(entry.getKey(), "UTF-8") + "="
                    + URLEncoder.encode(entry.getValue(), "UTF-8"));
        byte[] out = sj.toString().getBytes(StandardCharsets.UTF_8);
        int length = out.length;

        http.setFixedLengthStreamingMode(length);
        http.setRequestProperty("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
        http.connect();
        try(OutputStream os = http.getOutputStream()) {
            os.write(out);
        }

        //System.out.println(http.getInputStream());

        BufferedReader in = new BufferedReader(
                new InputStreamReader(http.getInputStream()));
        String inputLine;
        StringBuffer content = new StringBuffer();
        while ((inputLine = in.readLine()) != null) {
            content.append(inputLine);
        }
        in.close();
        System.out.println(content.toString());

        return "unimplemented";
    }

    public String post2(String path, Map<String, String> headers, Map<String, String> params, boolean checkCertificates) throws IOException, KeyManagementException {
        String url = "https://adrianus.ro";

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

        HttpsURLConnection httpClient = (HttpsURLConnection) new URL(url).openConnection();

        //add reuqest header
        httpClient.setRequestMethod("POST");
        //httpClient.setRequestProperty("User-Agent", "Mozilla/5.0");
        //httpClient.setRequestProperty("Accept-Language", "en-US,en;q=0.5");

        String urlParameters = "sn=C02G8416DRJM&cn=&locale=&caller=&num=12345";

        // Send post request
        httpClient.setDoOutput(true);
        try (DataOutputStream wr = new DataOutputStream(httpClient.getOutputStream())) {
            wr.writeBytes(urlParameters);
            wr.flush();
        }

        int responseCode = httpClient.getResponseCode();
        System.out.println("\nSending 'POST' request to URL : " + url);
        System.out.println("Post parameters : " + urlParameters);
        System.out.println("Response Code : " + responseCode);

        try (BufferedReader in = new BufferedReader(
                new InputStreamReader(httpClient.getInputStream()))) {

            String line;
            StringBuilder response = new StringBuilder();

            while ((line = in.readLine()) != null) {
                response.append(line);
            }

            //print result
            System.out.println(response.toString());

        }
        if (!checkCertificates) {
            HttpsURLConnection.setDefaultSSLSocketFactory(old);
        }
        return "unimplemented";
    }

    public String getFootballData(String path, Map<String, String> headers, Map<String, String> params, boolean checkCertificates) throws IOException, KeyManagementException {
        URL url = new URL(path);

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

        HttpURLConnection httpClient = (HttpURLConnection) url.openConnection();
        httpClient.setRequestMethod("GET");

        for (Map.Entry<String, String> header : headers.entrySet()) {
            httpClient.setRequestProperty(header.getKey(), header.getValue());
        }

        BufferedReader in = new BufferedReader(
                new InputStreamReader(httpClient.getInputStream()));
        String inputLine;
        StringBuffer content = new StringBuffer();
        while ((inputLine = in.readLine()) != null) {
            content.append(inputLine);
        }
        in.close();

        if (!checkCertificates) {
            HttpsURLConnection.setDefaultSSLSocketFactory(old);
        }
        return content.toString();
    }

    public static void main(String[] args) throws IOException, KeyManagementException {
        System.out.println("running RequestsClient v1.0");

        RequestsClient requestsClient = new RequestsClient();
        //String data = requestsClient.get("https://example.com");
        //System.out.println(data);
        //requestsClient.post(null, null, null);
        //requestsClient.post2(null, null, null, false);

        Map<String, String> headers = new HashMap<>();
        headers.put("X-Auth-Token", "f5c1f45ccb174b739541ad43203c7183");
        String football = requestsClient.getFootballData("https://api.football-data.org/v2/competitions/PL/matches", headers, null, false);
        System.out.println(football);
    }
}
