package repl;

import ast.nodes.AstProgram;
import compiler.Bytecode;
import compiler.Compiler;
import environment.Environment;
import evaluator.Evaluator;
import objects.AdIntegerObject;
import objects.AdObject;
import parser.Parser;
import vm.VM;

import java.util.Scanner;

public class Repl {
    private Scanner scanner;
    private Parser parser;
    private AstProgram program;
    private Evaluator evaluator;
    private Compiler compiler;
    private VM vm;

    public Repl() {
        scanner = new Scanner(System.in);
        parser = new Parser();
        program = new AstProgram();
        evaluator = new Evaluator();
        compiler = new Compiler();
        vm = new VM();
    }

    public void loop() {
        String line;
        Environment environment = new Environment();
        while (true) {
            System.out.print(">> ");
            line = scanner.nextLine();
            if (line.equals("exit()")) break;
            program.reset();
            parser.load(line);
            parser.buildStatements(program);
            //evaluator.eval(program, environment);
            compiler.init();
            compiler.compile(program);
            Bytecode bytecode = compiler.getBytecode();
            //compiler.getCode().setInstructions(bytecode.getInstructions());
            //System.out.println(compiler.getCode().print());
            vm.init(bytecode);
            vm.run();
            AdObject stackElem = vm.stackTop();
            System.out.println(((AdIntegerObject) stackElem).getValue());
        }
    }
}
