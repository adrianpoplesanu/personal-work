#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    std::ifstream in("syntax268.cpp");
    std::string text = "";
    if (in.is_open() ) {
        char mychar;
        while ( in ) {
            mychar = in.get();
            text += mychar;
        }
    }
    std::cout << text << "\n";
    return 0;
}