package ro.adrianus.chapter01.part01.executors;

import ro.adrianus.chapter01.part01.UnsafeSequence;

import static java.lang.Thread.sleep;

public class UnsafeSequenceExecutor {
    private UnsafeSequence unsafeSequence;

    public UnsafeSequenceExecutor(UnsafeSequence unsafeSequence) {
        this.unsafeSequence = unsafeSequence;
    }

    public Worker generateWorker(int index) {
        return new Worker(index, unsafeSequence);
    }

    class Worker implements Runnable {
        private UnsafeSequence unsafeSequence;
        private int index;

        public Worker(int index, UnsafeSequence unsafeSequence) {
            this.index = index;
            this.unsafeSequence = unsafeSequence;
        }

        @Override
        public void run() {
            try {
                sleep(1000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            System.out.println("thread-" + index + " got: " + unsafeSequence.getNext());
        }
    }

    public static void main(String[] args) {
        UnsafeSequence unsafeSequence = new UnsafeSequence();
        UnsafeSequenceExecutor unsafeSequenceExecutor = new UnsafeSequenceExecutor(unsafeSequence);
        for (int i = 0; i < 1000; i++) {
            Worker worker = unsafeSequenceExecutor.generateWorker(i);
            Thread t = new Thread(worker);
            t.start();
        }
        System.out.println("ended");
        System.out.println("main: " + unsafeSequence.getNext());
    }
}
