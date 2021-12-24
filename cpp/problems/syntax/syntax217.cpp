#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    std::ifstream in;
    std::ofstream out;

    in.open("README.md");
    std::string line;
    while (getline(in, line)) {
        std::cout << line << '\n';
    }
    in.close();

    return 0;
}
