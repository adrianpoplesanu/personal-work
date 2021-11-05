package repl;

import java.util.Scanner;

public class Repl {
    private Scanner scanner;

    public Repl() {
        scanner = new Scanner(System.in);
    }

    public void loop() {
        while(true) {
            System.out.print(">> ");
            String line = scanner.nextLine();
            if (line.equals("exit()")) break;
            if (!line.equals("")) System.out.println(line);
        }
    }
}
