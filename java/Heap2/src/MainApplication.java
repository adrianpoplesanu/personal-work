import repl.Repl;

public class MainApplication {
    public static void main(String[] args) {
        System.out.println("running Heap CLI...");
        Repl repl = new Repl();
        repl.loop();
    }
}
