import java.time.Duration;
import java.time.Instant;
import java.util.concurrent.atomic.AtomicInteger;

public class TestingVirtualThreads {

    Runnable runnable = () -> {
        System.out.println("Hello, world!");
    };

    public void test() {
        Thread virtualThread = Thread.startVirtualThread(runnable);

        virtualThread.start(); // asta o,o ridica exceptie legata de faptul ca threadul a pornit deja
        //virtualThread.join();
        //Thread.ofVirtual()
        //        .name("my-virtual-thread")
        //        .start(runnable);
    }

    public void test2() throws InterruptedException {
        Thread thread = Thread.ofVirtual().start(runnable);
        thread.join();
    }

    public void test3() throws InterruptedException {
        var i = 0;
        AtomicInteger count = new AtomicInteger(0);
        Instant start = Instant.now();
        while (i < 1000000) {
            Thread.startVirtualThread(() -> count.incrementAndGet());
            i++;
        }

        Thread.sleep(1000); // am nevoie de wait-ul asta aici ca sa astept sa termine executia tuturor celorlalte threaduri

        System.out.println(count.get());
        System.out.println(Duration.between(start, Instant.now()));
    }

    public void test4() throws InterruptedException {
        var i = 0;

        AtomicInteger counter = new AtomicInteger(0);
        Instant start = Instant.now();

        while ( i++ < 1_000_000) {
            Thread thread = Thread.ofVirtual().start(() -> counter.incrementAndGet() );
            thread.join();
        }

        int elapsedNanoSeconds = Duration.between(start, Instant.now()).getNano();
        System.out.println ((double) elapsedNanoSeconds / 100_000_000.0); // TODO: why not 9 zeros
        System.out.println(counter.get());
    }

    public static void main(String[] args) throws InterruptedException {
        TestingVirtualThreads testingVirtualThreads = new TestingVirtualThreads();
        //testingVirtualThreads.test();
        //testingVirtualThreads.test2();
        //testingVirtualThreads.test3();
        testingVirtualThreads.test4();
    }
}
