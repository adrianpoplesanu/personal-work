/*
   exercise: 023
   page: 154
   description: max heapify
   command: echo 10 1 2 3 4 7 8 9 10 14 16 | ./program023
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

#define PARENT(i)       ((i) >> 1)
#define LEFT(i)         ((i) << 1)
#define RIGHT(i)        (((i) << 1) + 1)

void max_heapify(int a[50], int n, int i) {
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
        max_heapify(a, n, largest);
    }
}

void build_max_heap(int a[50], int n) {
    for (int i = n / 2; i >= 1; i--) {
        max_heapify(a, n, i);
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

void pretty_print_heap(int a[], int n) {
    int height = std::floor(std::log2(n)) + 1;
    for (int j = 0; j < height; j++) std::cout << " ";
    int level_size = 1;
    int current_level = 1;
    for (int i = 1; i <= n; i++) {
        if (level_size == current_level) {
            std::cout << a[i] << "\n";
            height /= 2;
            for (int j = 0; j < height; j++) std::cout << " ";
            level_size *= 2;
            current_level = 0;
        } else {
            std::cout << a[i] << " ";
        }
        current_level++;
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);
    build_max_heap(a, n);
    print_array(a, n);
    pretty_print_heap(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

