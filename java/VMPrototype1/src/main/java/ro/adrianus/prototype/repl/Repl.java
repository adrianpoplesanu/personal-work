package ro.adrianus.prototype.repl;

import ro.adrianus.prototype.ast.AstProgram;
import ro.adrianus.prototype.evaluator.Evaluator;
import ro.adrianus.prototype.parser.Parser;

import java.util.Scanner;

public class Repl {
    private Scanner scanner = new Scanner(System.in);
    private Parser parser;
    private AstProgram program;
    private Evaluator evaluator;

    public Repl(Parser parser, AstProgram program, Evaluator evaluator) {
        this.parser = parser;
        this.program = program;
        this.evaluator = evaluator;
    }

    public void executeSource(String source) {

    }

    public void loop() {
        while(true) {
            System.out.print(">> ");
            String line = scanner.nextLine();
            if (line.equals("exit()")) break;
            parser.load(line);
            program.reset();
            parser.buildProgramStatements(program);
            //evaluator.eval(program, env);
        }
    }
}
