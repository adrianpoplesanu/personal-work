package repl;

import ast.nodes.AstProgram;
import environment.Environment;
import environment.EnvironmentUtils;
import evaluator.Evaluator;
import lexer.Lexer;
import parser.Parser;

import java.util.Scanner;

public class Repl {
    private Scanner scanner;
    private Parser parser;
    private Evaluator evaluator;

    public Repl() {
        scanner = new Scanner(System.in);
        parser = new Parser();
        evaluator = new Evaluator();
    }
    public void loop() {
        Environment environment = EnvironmentUtils.createEnvironment();
        while(true) {
            System.out.print(">> ");
            String line = scanner.nextLine();
            if ("exit".equals(line)) break;
            parser.load(line);
            AstProgram program = new AstProgram();
            program.reset();
            parser.buildProgramStatements(program);
            evaluator.eval(program, environment);
        }
    }

    public void executeFile() {
        
    }
}
