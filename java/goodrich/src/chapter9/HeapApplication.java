package chapter9;

public class HeapApplication {
    public static void main(String[] args) {
        HeapPriorityQueue<Integer, String> heap = new HeapPriorityQueue<>();
        heap.insert(4, "4");
        heap.insert(7, "7");
        heap.insert(9, "9");
        heap.insert(11, "11");
        heap.insert(13, "13");
        heap.insert(2, "2");
        for (int i = 0; i < heap.size(); i++) System.out.print(heap.elementAt(i).getValue() + " ");
        System.out.println("");
    }
}
