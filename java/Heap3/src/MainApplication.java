import heap.Heap;
import heap.HeapInterface;
import repl.Repl;

public class MainApplication {
    public static void main(String[] args) {
        HeapInterface heap = new Heap();
        Repl repl = new Repl(heap);
        repl.loop();
    }
}
