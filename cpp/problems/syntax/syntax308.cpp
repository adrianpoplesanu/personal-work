#include <iostream>
#include <ctime>
#include <memory>

int main(int argc, char *argv[]) {

    clock_t start = clock(); 

    for (int i = 0; i < 1000000; i++) {
        int *value = new int(5);
        (*value)++;
        delete value;
    }

    clock_t end = clock();
    std::cout << "ran for: " << double(end - start) / CLOCKS_PER_SEC << "\n";

    return 0;
}

// ran for: 0.031467
