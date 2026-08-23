/*
   exercise: 035
   page: 216
   description: iterative randomized select
   command: echo 9 3 8 2 7 1 6 -9 4 5 | ./program035
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

int partition(int a[], int p, int r) {
    int x = a[r];
    int k = p - 1;
    for(int i = p; i < r; i++) {
        if (a[i] < x) {
            k++;
            swap(a, k, i);
        }
    }
    swap(a, k + 1, r);
    return k + 1;
}

int randomized_partition(int a[], int p, int r) {
    int i = p + rand() % (r - p + 1);
    swap(a, r, i);
    return partition(a, p, r);
}

int iterative_randomized_select(int a[], int p, int r, int i) {
    while(p < r) {
        int q = randomized_partition(a, p, r);
        int k = q - p + 1;
        if (i == k) {
            return a[q];
        }
        if (i < k) {
           r = q - 1; 
        } else {
            p = q + 1;
            i = i - k;
        }
    }
    return a[p];
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);
    print_array(a, n);

    int val = iterative_randomized_select(a, 0, n - 1, 4);
    std::cout << "[ RESULT ] " << val << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

