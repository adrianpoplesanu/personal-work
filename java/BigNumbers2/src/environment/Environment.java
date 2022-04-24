package environment;

import objects.BNObject;

import java.util.HashMap;
import java.util.Map;

public class Environment {
    private Environment outer;
    private Map<String, BNObject> store;

    public Environment() {
        store = new HashMap<>();
    }

    public BNObject get(String key) {
        return store.get(key);
    }

    public void set(String key, BNObject obj) {
        store.put(key, obj);
    }
}
