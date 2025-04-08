package ro.adrianus.chapter01.part01;

import ro.adrianus.markings.NotThreadSafe;

@NotThreadSafe
public class UnsafeSequence {
    private int value;

    public int getNext() {
        return value++;
    }
}
