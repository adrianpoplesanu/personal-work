package repl;

import lexer.Lexer;
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
            String line = scanner.nextLine();
            if ("exit".equals(line)) break;
            parser.load(line);
            parser.buildProgramStatements();
        }
    }

    public void executeFile() {
        
    }
}
