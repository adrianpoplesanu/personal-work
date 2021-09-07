#include <iostream>

int main(int argc, char *argv[]) {
    std::hash<int> hash_int;
    std::hash<std::string> hash_string;

    std::cout << hash_int(123) << "\n";
    std::cout << hash_string("123") << "\n";

    return 0;
}
