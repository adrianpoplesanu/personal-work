import java.util.regex.Pattern;

public class RegexTester {
    private Pattern pattern;

    public RegexTester() {
        //...
    }

    public void testNoIgnoreCase() {
        pattern = Pattern.compile("BUNA DIMNEATA");
        boolean result = pattern.matcher("Buna dimineata").matches();
        System.out.println(result);
    }

    public void testIgnoreCase() {
        pattern = Pattern.compile("BUNA DIMINEATA", Pattern.CASE_INSENSITIVE);
        boolean result = pattern.matcher("Buna dimineata").matches();
        System.out.println(result);
    }
}
