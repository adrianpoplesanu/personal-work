package chapter1;

public class Counter {
    private int count;

    public Counter() {
        count = 0;
    }

    public Counter(int initial) {
        count = initial;
    }

    public int getCount() {
        return count;
    }

    public void increment() {
        count++;
    }

    public void inclement(int delta) {
        count += delta;
    }

    public void reset() {
        count = 0;
    }
}
