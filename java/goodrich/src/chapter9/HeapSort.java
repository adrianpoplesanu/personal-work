package chapter9;

import chapter7.PositionalList;

public class HeapSort {
    public static <E> void pqSoer(PositionalList<E> S, PriorityQueue<E, ?> P) {
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

    }
}
