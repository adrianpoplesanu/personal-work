/*
   exercise: 019
   page: 125
   description: permute by sorting priorities array
   command: echo 9 1 2 3 4 5 6 7 8 9 | ./program019
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

void sort_priorities(int a[50], int p[50], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (p[j] > p[j + 1]) {
                int tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;

                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

void permute_by_sorting(int a[50], int n) {
    int p[50];
    for (int i = 0; i < n; i++) {
        p[i] = rand() % (n * n * n);
    }
    sort_priorities(a, p, n);
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);

    srand(time(nullptr));
    permute_by_sorting(a, n);

    print_array(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

