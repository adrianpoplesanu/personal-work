package chapter9;

import chapter7.LinkedPositionalList;
import chapter7.Position;
import chapter7.PositionalList;

public class HeapSort {
    public static <E> void pqSort(PositionalList<E> S, PriorityQueue<E, ?> P) {
        int n = S.size();
        for (int j = 0; j < n; j++) {
            E element = S.remove(S.first());
            P.insert(element, null);
        }
        for (int j = 0; j < n; j++) {
            E element = P.removeMin().getKey();
            S.addLast(element);
        }
    }

    public static void main(String[] args) {
        PositionalList<Integer> numbers = new LinkedPositionalList<>();
        numbers.addLast(4);
        numbers.addLast(6);
        numbers.addLast(9);
        numbers.addLast(2);
        numbers.addLast(3);
        numbers.addLast(5);
        numbers.addLast(1);
        numbers.addLast(8);
        numbers.addLast(7);
        PriorityQueue<Integer, Integer> pq = new HeapPriorityQueue<>();
        pqSort(numbers, pq);
        for (Position<Integer> e : numbers.positions()) {
            System.out.print(e.getElement() + " ");
        }
    }
}
