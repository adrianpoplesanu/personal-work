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
        //if (outer != null && outer.store.containsKey(ident)) return outer.store.get(ident);
        if (outer != null) return outer.get(ident);
        return null;
    }

    public boolean containsInStore(String ident) {
        return store.containsKey(ident);
    }

    public boolean containsInOuter(String ident) {
        return outer.store.containsKey(ident);
    }

    public boolean containsInUpstream(String ident) {
        if (store.containsKey(ident)) {
            return true;
        } else if (outer != null) {
            return outer.containsInUpstream(ident);
        }
        return false;
    }

    public void addValueToStore(String ident, AdObject obj) {
        // declaring a variable explicit in scope triggers this, just line params passed through to a function
        store.put(ident, obj);
    }

    public void updateValueInUpstream(String ident, AdObject obj) {
        // this helps to re-assign-ing global or at least two level up variables
        if (store.containsKey(ident)) {
            store.put(ident, obj);
        } else {
            outer.updateValueInUpstream(ident, obj);
        }
    }
}
