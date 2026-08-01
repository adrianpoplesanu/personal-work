/*
   exercise: 000
   page: 00
   description: testing template
   command: echo 9 aaa lll sss kkk ddd jjj fff hhh ggg | ./program076
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    char a[50][50], tmp[50];
    int n, i, sorted = 0;
    std::cin >> n;
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    while(!sorted) {
        sorted = 1;
        for (i = 0; i < n - 1; i++) {
            if (strcmp(a[i], a[i + 1]) > 0) {
                sorted = 0;
                strcpy(tmp, a[i]);
                strcpy(a[i], a[i + 1]);
                strcpy(a[i + 1], tmp);
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

