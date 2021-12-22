#include <iostream>

int main(int argc, char*argv[]) {
    std::string command = "ls -la";
    system(command.c_str());
    return 0;
}
