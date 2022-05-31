package environment;

import objects.VObject;

import java.util.HashMap;
import java.util.Map;

public class Environment {
    private Environment outer;
    private Map<String, VObject> store = new HashMap<>();
}
