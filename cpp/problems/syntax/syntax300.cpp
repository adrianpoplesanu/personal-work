#include <iostream>
#include <ctime>

int main(int argc, char *argv[]) {
    clock_t begin = clock();

    int a[100000];
    int i = 0;
    while (i < 100000) {
        a[i] = i;
        i++;
    }

    clock_t end = clock();
    std::cout << "ran for: " << double(end - begin) / CLOCKS_PER_SEC << "sec\n";
    return 0;
}
