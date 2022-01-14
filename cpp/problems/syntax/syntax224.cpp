#include <iostream>
#include <sstream>
#include <map>

int main(int argc, char *argv[]) {
    std::string config = "key1:value1,key2:value2";
    std::map<std::string, std::string> configMap;
    std::stringstream config_stream(config);
    while(config_stream.good()) {
        std::string substr;
        getline(config_stream, substr, ',');
        //std::cout << substr << "\n";
        std::stringstream entry_stream(substr);
        while (entry_stream.good()) {
            std::string substr2;
            getline(entry_stream, substr2, ':');
            std::cout << substr2 << "\n";
        }
    }
    return 0;
}
