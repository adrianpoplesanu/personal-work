package repl;

import java.util.Scanner;

public class Repl {
    private Scanner scanner;

    public Repl() {
        scanner = new Scanner(System.in);
    }

    public void loop() {
        String line;
        while (true) {
            System.out.print(">> ");
            line = scanner.nextLine();
            if (line.equals("exit()")) break;
        }
    }
}
