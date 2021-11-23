package repl;

import java.util.Scanner;

public class Repl {
    private Scanner scanner;

    public Repl() {
        scanner = new Scanner(System.in);
    }

    public void loop() {
        String command;
        while(true) {
            command = scanner.nextLine();
            if (command.equals("exit")) {
                break;
            } else if (command.equals("print")) {

            } else if (command.equals("min")) {

            } else if (command.equals("remove")) {

            } else if (command.startsWith("add")) {

            }
        }
    }
}
