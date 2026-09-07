package chapter6;

public class Josephus {
    public static <E> E Josephus(CircularQueue<E> queue, int k) {
        if (queue.isEmpty()) return null;
        while(queue.size() > 1) {
            for (int i = 0; i < k - 1; i++) queue.rotate();;
            E e = queue.dequeue();
            System.out.println("      " + e + " is out");
        }
        return queue.dequeue();
    }

    public static <E> CircularQueue<E> buildQueue(E a[]) {
        CircularQueue<E> queue = new LinkedCircularQueue<>();
        for (int i = 0; i < a.length; i++) {
            queue.enqueue(a[i]);
        }
        return queue;
    }

    public static void main(String[] args) {
        String[] a1 = {"Alina", "Georgiana", "Izabela", "Ioana", "Crina"};
        String[] a2 = {"Cristina", "Roxana", "Gabriela", "Elena", "Mihaela"};
        String[] a3 = {"Dana", "Doina"};

        System.out.println("First winner is " + Josephus(buildQueue(a1), 3));
        System.out.println("Second winner is " + Josephus(buildQueue(a2), 10));
        System.out.println("Third winner is " + Josephus(buildQueue(a3), 7));
    }
}
