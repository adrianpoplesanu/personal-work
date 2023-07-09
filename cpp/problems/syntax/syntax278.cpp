#include <iostream>
#include <map>

void prettyPrint(std::map<std::string, int> pairs) {
    for(std::map<std::string, int>::iterator it = pairs.begin(); it != pairs.end(); it++) {
        std::cout << it->first << ": " << it->second << "\n";
    }
}

int main(int argc, char *argv[]) {
    std::map<std::string, int> pairs;
    pairs.insert(std::make_pair("aaa", 5));
    
    prettyPrint(pairs);

    pairs.insert(std::make_pair("aaa", 13));

    prettyPrint(pairs);

    std::map<std::string, int>::iterator it = pairs.find("aaa");
    if (it == pairs.end()) {
        pairs.insert(std::make_pair("aaa", 13));
    } else {
        it->second = 13;
    }

    prettyPrint(pairs);

    return 0;
}
