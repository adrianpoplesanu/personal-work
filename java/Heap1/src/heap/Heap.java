package heap;

public class Heap implements HeapInterface {
    private int[] heap;
    private int size;

    public Heap() {
        size = 0;
        heap = new int[100];
    }

    @Override
    public void insert(int e) {
        heap[size++] = e;
        int poz = size - 1;
        while(((poz - 1) / 2) >= 0 && (heap[(poz - 1) / 2] > heap[poz])) {
            int aux = heap[poz];
            heap[poz] = heap[(poz - 1) / 2];
            heap[(poz - 1) / 2] = aux;
            poz = (poz - 1) / 2;
        }
    }

    @Override
    public int min() {
        return heap[0];
    }

    @Override
    public int remove() {
        int result = heap[0];
        int poz = 0, next = -12, minChild = -11;
        boolean has_children;
        while (poz < size) {
            has_children = false;
            if (poz * 2 + 1 < size) {
                has_children = true;
                minChild = heap[poz * 2 + 1];
                next = poz * 2 + 1;
            }
            if (poz * 2 + 2 < size) {
                has_children = true;
                if (heap[poz * 2 + 2] < minChild) {
                    minChild = heap[poz * 2 + 2];
                    next = poz * 2 + 2;
                }
            }
            if (!has_children) break;
            heap[poz] = minChild;
            poz = next;
        }
        size--;
        return result;
    }

    @Override
    public void print() {
        for (int i = 0; i < size; i++) System.out.print(heap[i] + " ");
        System.out.println("");
    }
}
