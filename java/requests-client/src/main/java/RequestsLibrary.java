import java.util.Map;

public class RequestsLibrary implements Requests {
    @Override
    public String get(String path) {
        return null;
    }

    @Override
    public String post(String path, Map<String, String> headers, Map<String, String> arguments) {
        return post(path, headers, arguments, true);
    }

    @Override
    public String post(String path, Map<String, String> headers, Map<String, String> arguments, boolean checkCertificates) {
        return null;
    }
}
