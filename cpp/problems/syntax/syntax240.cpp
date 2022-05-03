#include <iostream>
#include <map>

int main(int argc, char *argv[]) {
    std::map<std::string, std::string> keywords = {
        {"aaa", "bbb"},
        {"bbb", "ccc"}
    };

    bool check = keywords.find("aaa") != keywords.end();
    std::cout << check << "\n";

    if (check) {
        std::cout << keywords.find("aaa")->second << "\n";
    }
    return 0;
}
