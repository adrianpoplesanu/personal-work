#include <iostream>

void change(int *a) {
    (*a)++;
}

int main(int argc, char *argv[]) {
    
    int *a = new int();
    *a = 5;

    std::cout << a << " " << *a << "\n";
    change(a);
    std::cout << a << " " << *a << "\n";

    delete a;

    return 0;
}
