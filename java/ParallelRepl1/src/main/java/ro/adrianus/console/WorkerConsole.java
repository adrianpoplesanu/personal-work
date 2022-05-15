package ro.adrianus.console;

import java.util.ArrayList;
import java.util.List;

public class WorkerConsole {
    private List<String> screen;
    private final static int CAPACITY = 20;

    public WorkerConsole() {
        screen = new ArrayList<String>();
    }

    public void addLine(String command) {
        if (screen.size() >= CAPACITY) {
            screen.remove(0);
            screen.add(CAPACITY - 1, command);
        } else {
            screen.add(command);
        }
    }

    public void print() {
        for (int i = 0; i < screen.size(); i++) {
            if (screen.get(i) != null) System.out.println(screen.get(i));
        }
    }
}
