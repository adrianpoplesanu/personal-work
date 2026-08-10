/*
   exercise: 000
   page: 00
   description: testing template
   command: echo 9 8 2 7 3 6 1 9 4 5 | ./program008_sanity_check2
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_array(int a[50], int &n) {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
}

void print_array(int a[50], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

void merge(int a[50], int low, int mid, int high) {
    int L[50];
    for (int i = low; i <= high; i++) {
        L[i] = a[i];
    }
    int i = low;
    int j = mid + 1;
    int k = low;
    while (i <= mid && j <= high) {
        if (L[i] < L[j]) {
            a[k++] = L[i++];
        } else {
            a[k++] = L[j++];
        }
    }
    while(i <= mid) {
        a[k++] = L[i++];
    }
    while(j <= high) {
        a[k++] = L[j++];
    }
}

void merge_sort(int a[50], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        merge_sort(a, low, mid);
        merge_sort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);
    merge_sort(a, 0, n - 1);
    print_array(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

