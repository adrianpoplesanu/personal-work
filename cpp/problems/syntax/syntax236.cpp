#include <iostream>

int main(int argc, char *argv[]) {
    std::string number = "555111122223333";
    int start = number.length() - 4, end = number.length();
    while (end > 0) {
        if (start < 0) start = 0;
        std::cout << number.substr(start, end - start) << "\n";
        end -= 4;
        start -= 4;
    }
    return 0;
}
