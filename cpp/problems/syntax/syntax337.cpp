#include <iostream>

typedef void(*func)();

int main(int argc, char *argv[]) {
    func a = []() { std::cout << "some output\n"; };
    a();
    return 0;
}
