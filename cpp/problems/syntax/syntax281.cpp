#include <iostream>

int main(int argc, char* args[]) {
    std::string a = "a";
    std::string b = "b";
    std::cout << a.compare(b) << "\n";
    std::cout << b.compare(a) << "\n";
    return 0;
}
