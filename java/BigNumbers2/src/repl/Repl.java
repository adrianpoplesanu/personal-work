package repl;

import lexer.Lexer;

import java.util.Scanner;

public class Repl {
    private Scanner scanner;
    private Lexer lexer;

    public Repl() {
        scanner = new Scanner(System.in);
        lexer = new Lexer();
    }
    public void loop() {
        while(true) {
            System.out.print(">> ");
            String line = scanner.nextLine();
            if ("exit".equals(line)) break;
            lexer.load(line);
        }
    }
}
