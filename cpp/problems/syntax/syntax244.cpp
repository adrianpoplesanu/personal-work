#include <iostream>
#include <map>

int main(int argc, char *argv[]) {
    std::map<std::string, std::string> keywords;

    keywords.insert(std::make_pair("unu", "1"));
    keywords.insert(std::make_pair("deux", "2"));
    keywords.insert(std::make_pair("three", "3"));

    if (keywords.find("unu") != keywords.end()) {
        std::cout << "l-am gasit\n";
        std::cout << keywords.at("unu") << "\n";
    }

    return 0;
}
