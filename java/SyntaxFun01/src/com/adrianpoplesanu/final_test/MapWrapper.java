package com.adrianpoplesanu.final_test;

import java.util.HashMap;
import java.util.Map;

public final class MapWrapper {
    private final Map<String, String> fields;

    public MapWrapper() {
        fields = new HashMap<>();
    }

    public void setFields(String name, String age) {
        fields.put(name, age);
    }

    public Map<String, String> getFields() {
        Map<String, String> result = new HashMap<>();
        result.put("bebe dex", fields.get("bebe dex"));
        result.put("ramunic", fields.get("ramunic"));
        return result;
    }
}
