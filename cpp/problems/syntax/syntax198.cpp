#include <iostream>

int main(int argc, char *argv[]) {
    std::hash<std::string> hash_string;
    std::cout << hash_string("buna dimineata!") << "\n";
    return 0;
}
