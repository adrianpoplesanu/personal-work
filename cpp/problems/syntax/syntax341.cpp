#include <iostream>

void test(int &a) {
    a = 7;
}

int main(int argc, char *argv[]) {
    int a = 5;
    std::cout << "[ LOG ] " << a << "\n";
    test(a);
    std::cout << "[ LOG ] " << a << "\n";
    return 0;
}
