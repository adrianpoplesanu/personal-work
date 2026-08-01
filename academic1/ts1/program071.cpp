/*
   exercise: 000
   page: 00
   description: testing template
   command: echo 123 | ./program020
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    char a[] = "bebe", b[] = "dex", c[] = "e", d[] = "micut", delim[] = " ";
    strcat(a, delim);
    strcat(a, b);
    strcat(a, delim);
    strcat(a, c);
    strcat(a, delim);
    strcat(a, d);
    std::cout << "[ RESULT ] " << a << "\n";
    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

