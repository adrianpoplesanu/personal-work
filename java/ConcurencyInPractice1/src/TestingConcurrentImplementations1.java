public class TestingConcurrentImplementations1 {

    public static void main(String[] args) throws InterruptedException {
        Thread thread1 = new Thread(() -> System.out.println("running1..."));
        Thread thread2 = new Thread(() -> System.out.println("running2..."));

        System.out.println("starting: " + thread1.getName());
        thread1.start();

        System.out.println("starting: " + thread2.getName());
        thread2.start();

        System.out.println("joining: " + thread1.getName());
        thread1.join();

        System.out.println("joining: " + thread2.getName());
        thread2.join();
    }
}
