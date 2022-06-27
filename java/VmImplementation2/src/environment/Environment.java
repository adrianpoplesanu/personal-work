package environment;

import objects.AdObject;

import java.util.HashMap;
import java.util.Map;

public class Environment {
    private Environment outer;
    private Map<String, AdObject> store;

    public Environment() {
        store = new HashMap<>();
    }

    public Environment(Environment outer) {
        store = new HashMap<>();
        this.outer = outer;
    }
}
