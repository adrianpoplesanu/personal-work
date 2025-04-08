package ro.adrianus.chapter01.part01.executors;

import ro.adrianus.chapter01.part01.Sequence;

import static java.lang.Thread.sleep;

public class SequenceExecutor {
    private Sequence sequence;

    public SequenceExecutor(Sequence sequence) {
        this.sequence = sequence;
    }

    public Worker generateWorker(int index) {
        return new Worker(index, sequence);
    }

    class Worker implements Runnable {
        private Sequence sequence;
        private int index;

        public Worker(int index, Sequence sequence) {
            this.index = index;
            this.sequence = sequence;
        }

        @Override
        public void run() {
            try {
                sleep(1000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            System.out.println("thread-" + index + " got: " + sequence.getNext());
        }
    }

    public static void main(String[] args) {
        Sequence sequence = new Sequence();
        SequenceExecutor sequenceExecutor = new SequenceExecutor(sequence);
        for (int i = 0; i < 1000; i++) {
            Worker worker = sequenceExecutor.generateWorker(i);
            Thread t = new Thread(worker);
            t.start();
        }
        System.out.println("ended");
        System.out.println("main: " + sequence.getNext());
    }
}
