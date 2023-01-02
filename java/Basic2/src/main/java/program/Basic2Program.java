package program;

import ast.ASTProgram;
import parser.Parser;

import java.util.Scanner;

public class Basic2Program {
    private Scanner scanner;
    private Parser parser;

    public Basic2Program() {
        scanner = new Scanner(System.in);
        parser = new Parser();
    }

    public void loop() {
        while (true) {
            System.out.print(">> ");
            String line = scanner.nextLine();
            if ("exit".equals(line)) break;
            parser.load(line);
            ASTProgram program = new ASTProgram();
            parser.parseProgram(program);
        }
    }
}
