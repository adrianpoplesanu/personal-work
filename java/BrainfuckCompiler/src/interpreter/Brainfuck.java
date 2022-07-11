package interpreter;

import java.util.*;

public class Brainfuck {
    private String source;
    private List<Command> commands;
    private Map<Character, CommandType> commandsMap;
    private int ptr[] = new int[1000];
    private int cp;

    public Brainfuck() {
        commands = new ArrayList<>();
        commandsMap = new HashMap<>();
        commandsMap.put('>', CommandType.MOVE_RIGHT);
        commandsMap.put('<', CommandType.MOVE_LEFT);
        commandsMap.put('+', CommandType.INCREMENT);
        commandsMap.put('-', CommandType.DECREMENT);
        commandsMap.put('.', CommandType.PRINT);
        commandsMap.put(',', CommandType.READ);
        commandsMap.put('[', CommandType.JUMP_FORWARD);
        commandsMap.put(']', CommandType.JUMP_BACKWARD);
    }

    public void load(String source) {
        this.source = source;
    }

    public void parse() {
        Stack<Integer> bracketStack = new Stack<>();
        for (int i = 0; i < source.length(); i++) {
            Command command = new Command(null, -1);
            if (commandsMap.containsKey(source.charAt(i))) {
                command.setType(commandsMap.get(source.charAt(i)));
                if (command.getType() == CommandType.JUMP_FORWARD) {
                    bracketStack.add(commands.size());
                }
                if (command.getType() == CommandType.JUMP_BACKWARD) {
                    int matchingBracket = bracketStack.pop();
                    command.setMatchingBracket(matchingBracket);
                    commands.get(matchingBracket).setMatchingBracket(commands.size());
                }
            } else {
                command.setType(CommandType.UNKNOWN);
            }
            commands.add(command);
        }
    }

    private void reset() {
        for (int i = 0; i < 1000; i++) ptr[i] = 0;
        cp = 0;
    }

    public void execute() {
        reset();
        int i = 0;
        while (i < commands.size()) {
            switch(commands.get(i).getType()) {
                case MOVE_RIGHT:
                    cp++;
                    break;
                case MOVE_LEFT:
                    cp--;
                    break;
                case INCREMENT:
                    ptr[cp]++;
                    break;
                case DECREMENT:
                    ptr[cp]--;
                    break;
                case PRINT:
                    System.out.print((char) ptr[cp]);
                    break;
                case READ:
                    // TODO: read from Scanner an int value
                    break;
                case JUMP_FORWARD:
                    if (ptr[cp] == 0) {
                        i = commands.get(i).getMatchingBracket();
                    }
                    break;
                case JUMP_BACKWARD:
                    if (ptr[cp] != 0) {
                        i = commands.get(i).getMatchingBracket();
                    }
                    break;
            }
            i++;
        }
    }
}
