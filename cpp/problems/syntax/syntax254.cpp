#include <iostream>
#include <map>

class Environment {
public:
    std::map<std::string, std::string> store;
    std::map<std::string, Environment*> siblings;

    Environment() {
        store.insert(std::pair<std::string, std::string>("token0", "bebe"));
        store.insert(std::pair<std::string, std::string>("token1", "dex"));
        store.insert(std::pair<std::string, std::string>("token2", "e"));
        store.insert(std::pair<std::string, std::string>("token3", "drabutz"));
    }
};

int main(int argc, char* argv[]) {
    std::cout << "testing map with Environment*\n";
    Environment *env = new Environment();
    return 0;
}
