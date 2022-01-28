package heap;

public class Heap implements HeapInterface {
    private int[] heap;
    private int size;

    public Heap() {
        heap = new int[100];
        size = 0;
    }

    @Override
    public void insert(int value) {
        heap[size++] = value;
        int poz = size - 1;
        while(poz > 0) {
            if (heap[(poz - 1) / 2] > heap[poz]) {
                int aux = heap[poz];
                heap[poz] = heap[(poz - 1) / 2];
                heap[(poz - 1) / 2] = aux;
                poz = (poz - 1) / 2;
            } else {
                break;
            }
        }
    }

    @Override
    public int min() {
        return heap[0];
    }

    @Override
    public int remove() {
        int result = heap[0];
        int poz = 0;
        while(poz < size) {
            boolean has_children = false;
            int temp = -11, next = -12;
            if (poz * 2 + 1 < size) {
                has_children = true;
                temp = heap[poz * 2 + 1];
                next = poz * 2 + 1;
            }
            if (poz * 2 + 2 < size) {
                has_children = true;
                if (heap[poz * 2 + 2] < temp) {
                    temp = heap[poz * 2 + 2];
                    next = poz * 2 + 2;
                }
            }
            if (!has_children) {
                for (int i = poz; i < size; i++) heap[i] = heap[i + 1];
                break;
            }
            heap[poz] = temp;
            poz = next;
        }
        size--;
        return result;
    }

    @Override
    public void print() {
        for (int i = 0; i < size; i++) System.out.print(heap[i] + " ");
        System.out.println();
    }
}
