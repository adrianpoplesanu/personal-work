/*
   exercise: 005
   page: 31
   description: merge sort
   command: echo 9 3 8 2 7 1 6 -9 4 5 | ./program007
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void merge(int a[], int p, int q, int r) {
    int L[50], R[50], i, j, k;
    int n1 = q - p + 1;
    int n2 = r - q;
    for (i = 0; i < n1; i++) {
        L[i] = a[p + i];
    }
    L[n1] = INT_MAX;
    for (j = 0; j < n2; j++) {
        R[j] = a[q + 1 + j];
    }
    R[n2] = INT_MAX;
    i = 0;
    j = 0;
    for (k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
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

