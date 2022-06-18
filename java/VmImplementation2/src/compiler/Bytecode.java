package compiler;

import code.utils.Instructions;
import objects.AdObject;

import java.util.ArrayList;
import java.util.List;

public class Bytecode {
    private Instructions instructions;
    private List<AdObject> constants;

    public Bytecode() {
        instructions = new Instructions();
        constants = new ArrayList<>();
    }

    public Instructions getInstructions() {
        return instructions;
    }

    public void setInstructions(Instructions instructions) {
        this.instructions = instructions;
    }

    public List<AdObject> getConstants() {
        return constants;
    }

    public void setConstants(List<AdObject> constants) {
        this.constants = constants;
    }
}
