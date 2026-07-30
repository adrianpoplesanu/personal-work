/*
   exercise: 063
   page: 208
   description: interclasare
   command: echo 4 1 4 7 9 4 2 3 5 8 | ./program063
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], b[50], c[50], n, m, i, j, k;
    std::cin >> n;
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::cin >> m;
    for(i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    i = 0;
    j = 0;
    k = 0;
    while(i < n && j < m) {
        if (a[i] < b[j]) {
            c[k++] = a[i++];
        } else {
            c[k++] = b[j++];
        }
    }
    while(i < n) {
        c[k++] = a[i++];
    }
    while(j < m) {
        c[k++] = b[j++];
    }

    std::cout << "[ RESULT ] ";
    for (i = 0; i < k; i++) {
        std::cout << c[i] << " ";
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

