package ro.adrianus.chapter01.part01;

import ro.adrianus.markings.GuardedBy;
import ro.adrianus.markings.ThreadSafe;

@ThreadSafe
public class Sequence {
    @GuardedBy("this") private int nextValue;

    public synchronized int getNext() {
        return nextValue++;
    }
}
