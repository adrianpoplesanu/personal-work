#include <iostream>
#include <ctime>

int main(int argc, char* argv[]) {
    clock_t start = clock();

    clock_t end = clock();
    std::cout << "ran for: " << (double) (end - start) / CLOCKS_PER_SEC << "\n";
    return 0;
}