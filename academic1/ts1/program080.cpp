/*
   exercise: 080
   page: 225
   description: strtok
   command: echo -e "ala bala, portocala ,,,bobab" | ./program080
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    char text[50], delim[] = " ,", *p;
    std::cin.get(text, 50);
    p = strtok(text, delim);
    std::cout << "[ RESULT ]\n";
    while(p) {
        std::cout << p << "\n";
        p = strtok(NULL, delim);
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

