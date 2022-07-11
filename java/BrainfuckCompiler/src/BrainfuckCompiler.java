import interpreter.Brainfuck;

public class BrainfuckCompiler {

    public static void main(String[] args) {
        Brainfuck brainfuck = new Brainfuck();
        brainfuck.load("++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.");
        brainfuck.parse();
        brainfuck.execute();
    }
}
