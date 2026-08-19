/*
   exercise: 031
   page: 185
   description: hoare partitioning, clrs version
   command: echo 9 3 8 2 7 1 6 -9 4 5 | ./program031
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_array(int a[], int &n) {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
}

void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

void swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int hoare_partition(int a[], int p, int r) {
    int x = a[p];
    int i = p - 1;
    int j = r + 1;
    while(true) {
        do { j--; } while (a[j] > x);
        do { i++; } while (a[i] < x);
        if (i < j) {
            swap(a, i, j);
        } else {
            return j;
        }
    }
}

void quicksort(int a[], int p, int r) {
    if (p < r) {
        int q = hoare_partition(a, p, r);
        quicksort(a, p, q);
        quicksort(a, q + 1, r);
    }
}


int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);
    print_array(a, n);

    quicksort(a, 0 , n - 1);
    print_array(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

