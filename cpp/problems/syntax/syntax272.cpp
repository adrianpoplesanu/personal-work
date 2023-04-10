#include <iostream>
#include <regex>

int main(int argc, char *argv[]) {
    std::string text = "aaa\nbbb";
    std::cout << text << "\n";

    std::string text2 = "aaa\\nbbb";
    std::cout << text2 << "\n";

    std::string a = "aaa\\nbbb";
    a = std::regex_replace(a, std::regex("\\\\n"), "\n");
    std::cout << a << "\n";

    return 0;
}