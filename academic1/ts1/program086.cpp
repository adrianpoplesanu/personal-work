/*
   exercise: 085
   page: 237
   description: testing template
   command: echo 8 a d r i a n u s | ./program085
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, i, j;
    char a[50];

    std::cin >> n;
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if ((int) a[j] > (int) a[j + 1]) {
                char tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }

    std::cout << "[ RESULT ] ";
    for (i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

