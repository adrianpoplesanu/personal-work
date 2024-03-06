#include<iostream>
#include<array>
#include<ctime>

int main(int argc, char *argv[]) {
    clock_t begin = clock();

    int a[1000];
    for (int j = 0; j < 1000; j++) a[j] = 0;

    int i = 0;
    while (i < 100000) {
        a[0] = i;
        i++;
    }

    clock_t end = clock();
    std::cout << "ran for: " << double(end - begin) / CLOCKS_PER_SEC << "sec\n";
    return 0;
}
