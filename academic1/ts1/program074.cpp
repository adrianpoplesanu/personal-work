/*
   exercise: 000
   page: 00
   description: testing template
   command: echo alabalaportocala a | ./program074
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    char a[100], c, *t;
    std::cin >> a >> c;
    t = a;
    std::cout << "[ RESULT ] ";
    while(t) {
        t = strchr(t, c);
        if (t) {
            std::cout << t - a << " ";
            t++;
        }
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

