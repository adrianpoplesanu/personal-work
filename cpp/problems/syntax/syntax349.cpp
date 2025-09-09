#include <iostream>

int main(int argc, char *argv[]) {
    std::string source = "aaa\nbbb";
    std::string result = source.substr(1, 4);
    std::cout << result;
    return 0;
}
