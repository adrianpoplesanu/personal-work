/*
   exercise: 005
   page: 31
   description: merge sort - using only one aux array
   command: echo 9 3 8 2 7 1 6 -9 4 5 | ./program008
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void merge(int a[], int p, int q, int r) {
    int aux[50], i, j, k;

    for (i = p; i <= q; i++) {
        aux[i] = a[i];
    }
    for (j = q + 1; j <= r; j++) {
        aux[j] = a[j];
    }
    i = p;
    j = q + 1;
    k = p;

    while(i <= q && j <= r) {
        if (aux[i] < aux[j]) {
            a[k++] = aux[i++];
        } else {
            a[k++] = aux[j++];
        }
    }
    while(i <= q) {
        a[k++] = aux[i++];
    }
    while(j <= r) {
        a[k++] = aux[j++];
    }
}

void merge_sort(int a[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(a, p, q);
        merge_sort(a, q + 1, r);
        merge(a, p, q, r);
    }
}

void read_array(int a[], int &n) {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
}

void print_array(int a[], int n) {
    for(int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);
    print_array(a, n);
    std::cout << "\n";
    merge_sort(a, 0, n - 1);
    print_array(a, n);
    std::cout << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

