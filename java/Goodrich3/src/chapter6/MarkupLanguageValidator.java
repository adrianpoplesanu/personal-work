package chapter6;

public class MarkupLanguageValidator {
    public static boolean isHTMLMatched(String html) {
        Stack<String> buffer = new LinkedStack<>();
        int j = html.indexOf('<');
        while (j != -1) {
            int k = html.indexOf('>', j + 1);
            if (k == -1) {
                return false;
            }
            String tag = html.substring(j + 1, k);
            if (!tag.startsWith("/")) {
                buffer.push(tag);
            } else {
                if (buffer.isEmpty()) {
                    return false;
                }
                if (!tag.substring(1).equals(buffer.pop())) {
                    return false;
                }
            }
            j = html.indexOf('<', k + 1);
        }
        return buffer.isEmpty();
    }

    public static void main(String[] args) {
        String html = "<head></head><body><h1>Bebe Dex</h1></body>";
        System.out.println(isHTMLMatched(html));

        String invalid = "<head></body></head><h1>Bebe Dex</h1><body>";
        System.out.println(isHTMLMatched(invalid));
    }
}
