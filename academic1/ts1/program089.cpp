/*
   exercise: 088
   page: 238
   description: smaller supra unitary number with ratio for array
   command: echo 9 1 2 3 9 8 7 4 5 6 | ./program089
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

void determine_smallest_ratio(int a[50], int n) {
    float smallest = (float)(a[1]) / (float)(a[0]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if ((float)(a[j]) / (float)(a[i]) < smallest && (float)(a[j]) / (float)(a[i]) > 1.0) {
                    smallest = (float)(a[j]) / (float)(a[i]);
                }
            }
        }
    }
    std::cout << "[ RESULT ] " << smallest << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);
    determine_smallest_ratio(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

