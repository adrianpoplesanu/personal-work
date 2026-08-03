/*
   exercise: 078
   page: 224
   description: remove all substrings from string
   command: echo -e "ala bala portocala\nala" | ./program078
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    char text[100], lookup[100], *p;
    std::cin.get(text, 100);
    std::cin.get();
    std::cin.get(lookup, 100);

    int len = strlen(lookup);
    p = strstr(text, lookup);
    while(p) {
        strcpy(p, p + len);
        p = strstr(p, lookup);
    }
    std::cout << "[ RESULT ] " << text << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

