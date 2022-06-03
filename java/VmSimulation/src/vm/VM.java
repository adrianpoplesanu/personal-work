package vm;

import code.Instructions;
import objects.VObject;

import java.util.ArrayList;
import java.util.List;

public class VM {
    public final static int stackSize = 2048;

    public Instructions instructions;
    public List<VObject> constants = new ArrayList<>();
}
