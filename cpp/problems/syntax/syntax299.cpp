// ran for: 0.008073sec
#include <iostream>
#include <ctime>

int main(int argc, char *argv[]) {
    clock_t begin = clock();

    int i = 0;
    while(i < 100000) {
        int *a = new int();
        i++;
        delete a;
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "ran for: " << elapsed_secs << "sec\n";
    return 0;
}
