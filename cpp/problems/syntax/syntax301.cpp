#include <iostream>
#include <ctime>
#include <vector>

int main(int argc, char *argv[]) {
    clock_t begin = clock();

    std::vector<int> a;
    int i = 0;
    while (i < 100000) {
        a.push_back(i);
        i++;
    }

    clock_t end = clock();
    std::cout << "ran for: " << double(end - begin) / CLOCKS_PER_SEC << "sec\n";
    return 0;
}
