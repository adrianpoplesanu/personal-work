#include <iostream>

void * operator new(size_t size) {
    std::cout << "allocating " << size << " bytes\n";
    return malloc(size);
}

int main(int argc, char *argv[]) {
    int *a = new int(5);
    return 0;
}
