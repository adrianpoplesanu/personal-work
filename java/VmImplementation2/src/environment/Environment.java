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

    public void insertStore(String ident, AdObject obj) {
        store.put(ident, obj);
    }

    public void insertOuter(String ident, AdObject obj) {
        outer.store.put(ident, obj);
    }

    public AdObject get(String ident) {
        if (store.containsKey(ident)) return store.get(ident);
        if (outer != null && outer.store.containsKey(ident)) return outer.store.get(ident);
        return null;
    }
}
