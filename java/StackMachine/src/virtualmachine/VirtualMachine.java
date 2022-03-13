package virtualmachine;

import java.util.List;
import java.util.Stack;

public class VirtualMachine {
    private Stack<Integer> stack;

    public VirtualMachine() {
        stack = new Stack<Integer>();
    }

    public VirtualMachine(String[] commands) {
        this();
        execute(commands);
    }

    public VirtualMachine(List<String> commands) {
        this();
        execute(commands);
    }

    private void execute(String[] commands) {
        int i = 0;
        while(i < commands.length) {

        }
    }

    private void execute(List<String> commands) {
        int i = 0;
        while(i < commands.size()) {
            
        }
    }

    private void push() {
        // ...
    }

    private void add() {
        // ...
    }

    private void minus() {
        // ...
    }
}
