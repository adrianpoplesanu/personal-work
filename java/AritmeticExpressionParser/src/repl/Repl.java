package repl;

import parser.Parser;

import java.util.Scanner;

public class Repl {
    private Scanner scanner;
    private Parser parser;

    public Repl() {
        scanner = new Scanner(System.in);
        parser = new Parser();
    }

    public void loop() {
        while(true) {
            System.out.print(">> ");
            String source = scanner.nextLine();
            if (source.equals("exit()")) break;
            if (source.equals("")) continue;
            parser.load(source);
            parser.buildStatements();
        }
    }
}
