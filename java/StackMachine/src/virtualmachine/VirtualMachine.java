package virtualmachine;

import java.util.List;
import java.util.Stack;

public class VirtualMachine {
    private String[] commands;
    private Stack<Integer> stack;
    private int programCounter;
    private int stackPointer;

    public VirtualMachine() {
        stack = new Stack<Integer>();
        programCounter = 0;
        stackPointer = 0;
    }

    public VirtualMachine(String[] commands) {
        this();
        this.commands = commands;
    }

    public VirtualMachine(List<String> commands) {
        this();
        this.commands = (String[]) commands.toArray();
    }

    public void execute() {
        programCounter = 0;
        stackPointer = 0;
        while(programCounter < commands.length) {
            switch(commands[programCounter]) {
                case "PUSH":
                    push(commands[programCounter + 1]);
                    break;
                case "ADD":
                    add();
                    break;
                case "MINUS":
                    minus();
                    break;
            }
            programCounter++;
        }
        printStacktop();
    }

    private void push(String number) {
        stack.push(Integer.valueOf(number));
        programCounter++;
        stackPointer++;
    }

    private void add() {
        int right = stack.pop();
        stackPointer--;
        int left = stack.pop();
        stackPointer--;
        stack.push(right + left);
        stackPointer++;
    }

    private void minus() {
        int right = stack.pop();
        stackPointer--;
        int left = stack.pop();
        stackPointer--;
        stack.push(left - right);
        stackPointer++;
    }

    private void printStacktop() {
        System.out.println("Stacktop: " + stack.peek() + " StackPointer: " + stackPointer);
    }
}
