#include <iostream>
#include <sstream>
#include <map>

int main(int argc, char *argv[]) {
    std::string config = "key1:value1,key2:value2";
    std::map<std::string, std::string> configMap;
    std::stringstream stream(config);
    while(stream.good()) {
        std::string substr;
        getline(stream, substr, ',');
        std::cout << substr << "\n";
    }
    return 0;
}
