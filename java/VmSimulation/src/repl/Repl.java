package repl;

import ast.AstProgram;
import environment.Environment;
import environment.EnvironmentUtils;
import evaluator.Evaluator;
import parser.Parser;

import java.util.Scanner;

public class Repl {
    private Scanner scanner;
    private Parser parser;
    private AstProgram astProgram;
    private Evaluator evaluator;

    public Repl () {
        scanner = new Scanner(System.in);
        parser = new Parser();
        astProgram = new AstProgram();
        evaluator = new Evaluator();
    }

    public void loop () {
        Environment env = EnvironmentUtils.newEnvironment();
        boolean running = true;
        while (running) {
            System.out.print(">> ");
            String line = scanner.nextLine();
            if (line.equals("exit()")) running = false;
            else {
                parser.load(line);
                astProgram.reset();
                parser.buildProgramStatements(astProgram);
                evaluator.eval(astProgram, env);
            }
        }
    }
}
