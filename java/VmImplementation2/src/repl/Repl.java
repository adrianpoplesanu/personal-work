package repl;

import ast.nodes.AstProgram;
import parser.Parser;

import java.util.Scanner;

public class Repl {
    private Scanner scanner;
    private Parser parser;
    private AstProgram program;

    public Repl() {
        scanner = new Scanner(System.in);
        parser = new Parser();
        program = new AstProgram();
    }

    public void loop() {
        String line;
        while (true) {
            System.out.print(">> ");
            line = scanner.nextLine();
            if (line.equals("exit()")) break;
            program.reset();
            parser.load(line);
            parser.buildStatements(program);
        }
    }
}
