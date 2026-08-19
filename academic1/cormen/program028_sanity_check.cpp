/*
   exercise: 000
   page: 00
   description: quicksort with 2 partitioning versions
   command: echo 9 8 2 7 3 6 4 -9 5 1 | ./program028_sanity_check
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

int partition(int a[], int low, int high) {
    // 5 1 2 9 3 9 9 ...
    // i = 1; k = 0 => 5 1 2 9 3 9 9 ... & k = 1
    // i = 2; k = 1 => 5 1 2 9 3 9 9 ... & k = 2
    // i = 3; k = 2 => 5 1 2 9 3 9 9 ... & k = 2
    // i = 4; k = 2 => 5 1 2 3 9 9 9 ... & k = 3
    // ...
    // la final swap 0 cu 3 => 3 1 2 5 9 9 9 ...
    int reference = a[low];
    int k = low;
    for (int i = low + 1; i <= high; i++) {
        if (a[i] < reference) {
            k++;
            swap(a, i, k);
        }
    }
    swap(a, k, low);
    return k;
}

int partition2(int a[], int low, int high) {
    // 1 2 9 3 9 9 5 ...
    // i = 0, k = -1 => 1 2 9 3 9 9 5 ... & k = 0
    // i = 1, k = 0  => 1 2 9 3 9 9 5 ... & k = 1
    // i = 2, k = 1  => 1 2 9 3 9 9 5 ... & k = 1
    // i = 3, k = 1  => 1 2 3 9 9 9 5 ... & k = 2
    // ...
    // la final swap 6 (high) cu 3 (k + 1) => 1 2 3 5 9 9 9 
    int reference = a[high];
    int k = low - 1;
    for (int i = low; i <= high; i++) {
        if (a[i] < reference) {
            k++;
            swap(a, i, k);
        }
    }
    swap(a, k + 1, high);
    return k + 1;
}


void quicksort(int a[], int low, int high) {
    if (low < high) {
        int pivot = partition(a, low, high);
        quicksort(a, low, pivot - 1);
        quicksort(a, pivot + 1, high);
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);
    print_array(a, n);

    quicksort(a, 0, n - 1);
    print_array(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

