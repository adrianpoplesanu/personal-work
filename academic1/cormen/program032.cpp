/*
   exercise: 031
   page: 195
   description: counting sort
   command: echo 8 5 2 5 3 0 2 3 0 3 | ./program031
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_array(int a[], int &n, int &k) {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
}

void print_array(int a[], int n) {
    for (int i = 1; i <= n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

void counting_sort(int a[], int b[], int n, int k) {
    int c[k + 1];
    for (int i = 0; i <= k; i++) {
        c[i] = 0;
    }
    for (int j = 1; j <= n; j++) {
        c[a[j]] = c[a[j]] + 1;
    }
    for (int i = 1; i <= k; i++) {
        c[i] = c[i] + c[i - 1];
    }
    for (int j = n; j >= 1; j--) {
        b[c[a[j]]] = a[j];
        c[a[j]] = c[a[j]] - 1;
    }

    /*for (int i = 0; i <= k; i++) {
        std::cout << c[i] << " ";
    }
    std::cout << "\n";*/
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], b[50], n, k;
    read_array(a, n, k);
    print_array(a, n);

    counting_sort(a, b, n, k);
    print_array(b, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

