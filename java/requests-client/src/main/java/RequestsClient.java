import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Map;

public class RequestsClient {

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

    public String post(String path, Map<String, String> headers, Map<String, String> params) {
        return "unimplemented";
    }

    public static void main(String[] args) throws IOException {
        System.out.println("running RequestsClient v1.0");

        RequestsClient requestsClient = new RequestsClient();
        String data = requestsClient.get("https://example.com");
        System.out.println(data);
    }
}
