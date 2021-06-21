#include <iostream>

int main(int argc, char *argv[]) {
    int a[] = { 1, 2, 3 };
    //int b[]; // nope;
    int *b;
    int c[10];
    //memset(b, 0, 10 * sizeof(*b)); // nope;
    memset(c, 0, sizeof(c)); // this works
    //memset(c, 80, sizeof(c)); // nope;
    b = new int[10]; // this works
    for (int i = 0; i < 10; i++) b[i] = i*i;
    for (int i = 0; i < 10; i++) std::cout << b[i] << " ";
    std::cout << "\n";
    for (int i = 0; i < 10; i++) std::cout << c[i] << " ";
    std::cout << "\n";
    return 0;
}
