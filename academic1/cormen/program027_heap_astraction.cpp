/*
   exercise: 000
   page: 00
   description: testing template
   command: echo 123 | ./program020
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

#define PARENT(i)       ((i) >> 1)
#define LEFT(i)         ((i) << 1)
#define RIGHT(i)        (((i) << 1) + 1)

enum HeapType {
    MAX,
    MIN,
    UNDEFINED
};

template <typename T>
class Heap {
    T a[100];
    int n;
    HeapType type;

public:
    Heap() {
        n = 0;
        type = MAX;
    }

    Heap(T a[], int n, HeapType t) {
        this->n = n;
        this->type = t;
        for(int i = 1; i <= n; i++) {
            this->a[i] = a[i];
        }
    }

    Heap(Heap const &original) {
        n = original.n;
        type = original.type;
        for (int i = 1; i <= n; i++) {
            a[i] = original.a[i];
        }
    }

    void load(T b[], int m) {
        n = m;
        for (int i = 0; i < n; i++) {
            a[i + 1] = b[i];
        }
    }

    void max_heapify(int i) {
        int l = LEFT(i);
        int r = RIGHT(i);
        int largest;
        if (l <= n && a[l] > a[i]) {
            largest = l;
        } else {
            largest = i;
        }
        if (r <= n && a[r] > a[largest]) {
            largest = r;
        }
        if (largest != i) {
            T tmp = a[i];
            a[i] = a[largest];
            a[largest] = tmp;
            max_heapify(largest);
        }
    }

    void build_max_heap() {
        for (int i = n / 2; i >= 1; i--) {
            max_heapify(i);
        }
    }

    T heap_maximum() {
        return a[1];
    }

    T heap_extract_max() {
        if (n < 1) {
            std::cout << "[ ERROR ] heap underflow\n";
            return;
        }
        T max = a[1];
        a[1] = a[n];
        n--;
        max_heapify(1);
        return max;
    }

    void heap_increase_key(int i, T key) {
        if (a[i] > key) {
            std::cout << "[ ERROR ] increased key smaller than original\n";
            return;
        }
        a[i] = key;
        while (i > 1 && PARENT(i) < a[i]) {
            T tmp = a[i];
            a[i] = a[PARENT(i)];
            a[PARENT(i)] = tmp;
            i = PARENT(i);
        }
    }

    void max_heap_insert(T key) {
        n++;
        int i = n;
        a[i] = key;
        while (i > 1 && a[PARENT(i)] < a[i]) {
            T tmp = a[i];
            a[i] = a[PARENT(i)];
            a[PARENT(i)] = tmp;
            i = PARENT(i);
        }
    }

    void min_heapify(int i) {
        int l = LEFT(i);
        int r = RIGHT(i);
        int smallest;
        if (l <= n && a[l] < a[i]) {
            smallest = l;
        } else {
            smallest = i;
        }
        if (r <= n && a[r] < a[smallest]) {
            smallest = r;
        }
        if (smallest != i) {
            T tmp = a[i];
            a[i] = a[smallest];
            a[smallest] = tmp;
            min_heapify(smallest);
        }
    }

    void build_min_heap() {
        for (int i = n / 2; i >= 1; i--) {
            min_heapify(i);
        }
    }

    void heap_minimum() {
        return a[1];
    }

    T heap_extract_min() {
        if (n < 1) {
            std::cout << "[ ERROR ] heap underflow\n";
            return;
        }
        T min = a[1];
        a[1] = a[n];
        n--;
        min_heapify(1);
        return min;
    }

    void heap_decrease_key(int i, T key) {
        if (a[i] < key) {
            std::cout << "[ ERROR ] decreased key larger than original\n";
            return;
        }
        a[i] = key;
        while (i > 1 && a[PARENT(i)] > a[i]) {
            T tmp = a[i];
            a[i] = a[PARENT(i)];
            a[PARENT(i)] = tmp;
            i = PARENT(i);
        }
    }

    void min_heap_insert(T key) {
        n++;
        int i = n;
        a[i] = key;
        while (i > 1 && a[PARENT(i)] > a[i]) {
            T tmp = a[i];
            a[i] = a[PARENT(i)];
            a[PARENT(i)] = tmp;
            i = PARENT(i);
        }
    }

    void print() {
        for (int i = 1; i <= n; i++) {
            std::cout << a[i] << " ";
        }
        std::cout << "\n";
    }

    void pretty_print() {
        int level = 1;
        int current = 0;
        for (int i = 1; i <= n; i++) {
            std::cout << a[i] << " ";
            current++;
            if (current == level) {
                level *= 2;
                current = 0;
                std::cout << "\n";
            }
        }
        std::cout << "\n";
    }
};

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    Heap<int> heap;
    int a[] = {33, 78, 24, 65,45, 89, 12, 34, 56}, n = 9;

    heap.load(a, n);
    heap.build_max_heap();
    heap.print();
    heap.pretty_print();

    heap.heap_increase_key(7, 97);
    heap.pretty_print();

    heap.max_heap_insert(10);
    heap.max_heap_insert(11);
    heap.max_heap_insert(12);
    heap.max_heap_insert(13);
    heap.max_heap_insert(14);
    heap.max_heap_insert(98);
    heap.pretty_print();

    Heap<int> heap2;
    int b[] = {89, 35, 56, 12, 87, 45, 55, 66, 37, 67}, m = 9;

    heap2.load(b, m);
    heap2.build_min_heap();
    heap2.print();
    heap2.pretty_print();

    heap2.heap_decrease_key(6, 11);
    heap2.pretty_print();

    heap2.min_heap_insert(21);
    heap2.min_heap_insert(22);
    heap2.min_heap_insert(23);
    heap2.min_heap_insert(24);
    heap2.min_heap_insert(25);
    heap2.min_heap_insert(26);
    heap2.min_heap_insert(10);
    heap2.pretty_print();

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

