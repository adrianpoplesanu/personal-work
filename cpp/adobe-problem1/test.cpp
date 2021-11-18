#include <iostream>
#include <fstream>
#include <regex>

int main(int argc, char *argv[]) {
    std::ifstream in("data.txt");
    std::string word;

    while (in >> word) {
        word = std::regex_replace(word, std::regex(","), "");
        std::cout << word << '\n';
    }

    return 0;
}
