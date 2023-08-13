// sorting a map by its string keys

#include <iostream>
#include <map>

int main(int argc, char *argv[]) {
    std::map<std::string, std::string> store;

    store["d"] = "bedus";
    store["b"] = "e";
    store["c"] = "catelus";
    store["a"] = "dragutz";

    for(std::map<std::string, std::string>::const_iterator it = store.begin(); it != store.end(); ++it) {
        std::cout << it->first << ": " << it->second << "\n";
    }

    return 0;
}
