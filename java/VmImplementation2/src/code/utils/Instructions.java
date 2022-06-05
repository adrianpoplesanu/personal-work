package code.utils;

import java.util.ArrayList;
import java.util.List;

public class Instructions {
    private List<Byte> instructions;

    public Instructions() {
        instructions = new ArrayList<>();
    }

    public List<Byte> getInstructions() {
        return instructions;
    }

    public int size() {
        return instructions.size();
    }

    public Byte get(int i) {
        return instructions.get(i);
    }

    public void add(Byte code) {
        instructions.add(code);
    }

    // TODO: add public methods that retrieve data
}
