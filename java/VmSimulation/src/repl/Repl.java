package repl;

import ast.AstProgram;
import compiler.Bytecode;
import compiler.Compiler;
import environment.Environment;
import environment.EnvironmentUtils;
import evaluator.Evaluator;
import objects.VIntegerObject;
import objects.VObject;
import parser.Parser;
import vm.VM;

import java.util.Scanner;

public class Repl {
    private Scanner scanner;
    private Parser parser;
    private AstProgram astProgram;
    private Evaluator evaluator;
    private Compiler compiler;
    private VM vm;

    public Repl () {
        scanner = new Scanner(System.in);
        parser = new Parser();
        astProgram = new AstProgram();
        evaluator = new Evaluator();
        compiler = new Compiler();
        vm = new VM();
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

                compiler.init();
                compiler.compile(astProgram);
                Bytecode bytecode = compiler.bytecode();

                vm.init(bytecode);
                vm.run();
                VObject stackElem = vm.stackTop();
                System.out.println(((VIntegerObject) stackElem).value);
            }
        }
    }
}
