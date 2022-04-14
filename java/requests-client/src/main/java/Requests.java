import java.util.Map;

public interface Requests {
    String get(String path);
    String post(String path, Map<String, String> headers, Map<String, String> arguments);
    String post(String path, Map<String, String> headers, Map<String, String> arguments, boolean checkCertificates);
}
