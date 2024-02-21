#include<iostream>
#include<unordered_map>

int main(int argc, char *argv[]) {
    std::unordered_map<std::string, int> data;
    data["dex"] = 4;
    std::cout << data["dex"] << "\n";
    //std::cout << data.find("bbb") << "\n";
    //std::cout << data["aaa"] << "\n";
    if (data.find("aaa") == data.end()) {
        std::cout << "not found!\n";
    }

    for (const std::pair<const std::string, int>& el : data) {
        std::cout << el.first << ": " << el.second << "\n";
    }
    return 0;
}
