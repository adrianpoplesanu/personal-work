#include <iostream>
#include <ctime>

int main(int argc, char *argv[]) {
    clock_t begin = clock();
    int i = 0;
    while (i < 1000) { 
        std::cout << i << "\n";
        i++;
    }
    clock_t end = clock();
    std::cout << "ran for: " << double(end - begin) / CLOCKS_PER_SEC << "sec\n";
    return 0;
}
