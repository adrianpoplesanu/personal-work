package ro.adrianus.prototype;

import ro.adrianus.prototype.ast.AstProgram;
import ro.adrianus.prototype.evaluator.Evaluator;
import ro.adrianus.prototype.parser.Parser;
import ro.adrianus.prototype.repl.Repl;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Ad {
    public static void main(String[] args) {
        if (args.length > 0) {
            String filename = args[0];
            String source;
            try {
                source = new String(Files.readAllBytes(Paths.get(filename)));
            } catch (IOException e) {
                source = "";
            }

            Parser parser = new Parser();
            AstProgram program = new AstProgram();
            Evaluator evaluator = new Evaluator();
            Repl repl = new Repl(parser, program, evaluator);
            repl.executeSource(source);
        } else {
            System.out.println("Ad compiler prototype + VM [JAVA]... v0.1");
            Parser parser = new Parser();
            AstProgram program = new AstProgram();
            Evaluator evaluator = new Evaluator();
            Repl repl = new Repl(parser, program, evaluator);
            repl.loop();
        }
    }
}
