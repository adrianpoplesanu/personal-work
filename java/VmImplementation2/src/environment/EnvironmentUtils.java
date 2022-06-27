package environment;

public class EnvironmentUtils {
    public static Environment newEnvironment() {
        return new Environment();
    }

    public static Environment newEnvironment(Environment outer) {
        return new Environment(outer);
    }
}
