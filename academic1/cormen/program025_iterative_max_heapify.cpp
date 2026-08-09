/*
   exercise: 025
   page: 160
   description: heap sort
   command: echo 10 6 16 7 14 8 12 9 1 2 3 | ./program025_iterative_max_heapify
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

#define PARENT(i)       ((i) >> 1)
#define LEFT(i)         ((i) << 1)
#define RIGHT(i)        (((i) << 1) + 1)

void iterative_max_heapify(int a[50], int n, int i) {
    while ( i < n) {
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
            int tmp = a[i];
            a[i] = a[largest];
            a[largest] = tmp;
            i = largest;
        } else {
            return;
        }
    }
}

void build_max_heap(int a[50], int n) {
    for (int i = n / 2; i >= 1; i--) {
        iterative_max_heapify(a, n, i);
    }
}

void read_array(int a[], int &n) {
    int i;
    std::cin >> n;
    for(i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
}

void print_array(int a[], int n) {
    for (int i = 1; i <= n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

void heapsort(int a[50], int n) {
    build_max_heap(a, n);
    for (int i = n; i >= 2; i--) {
        int tmp = a[1];
        a[1] = a[i];
        a[i] = tmp;
        iterative_max_heapify(a, i - 1, 1);
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);
    heapsort(a, n);
    print_array(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

