#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]) {
    std::ifstream in("syntax216.cpp");
    std::string content = "";
    std::stringstream buffer;
    buffer << in.rdbuf();
    content = buffer.str();
    std::cout << content << "\n";
    return 0;
}
