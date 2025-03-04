// echo "qwe asd zxc" | ./syntax342 

#include <iostream>

int main(int argc, char *argv[]) {
    std::string s;
    std::getline(std::cin, s);
    const char *ps = s.c_str();
    std::cout << ps << "\n";
    return 0;
}
