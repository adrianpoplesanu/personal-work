package program;

import ast.ASTProgram;
import environment.Environment;
import evaluator.Evaluator;
import parser.Parser;
import utils.ASTNodeUtils;

import java.util.Scanner;

public class Basic2Program {
    private Scanner scanner;
    private Parser parser;
    private Evaluator evaluator;
    private Environment env;

    public Basic2Program() {
        scanner = new Scanner(System.in);
        parser = new Parser();
        evaluator = new Evaluator();
        env = new Environment();
    }

    public void loop() {
        while (true) {
            System.out.print(">> ");
            String line = scanner.nextLine();
            if ("exit".equals(line)) break;
            parser.load(line);
            ASTProgram program = new ASTProgram();
            parser.parseProgram(program);
            //ASTNodeUtils.printASTNode(program, 0);
            evaluator.eval(program, env);
        }
    }
}
