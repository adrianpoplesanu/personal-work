#include <iostream>
#include <thread>
#include <vector>

class ThreadPool {
public:
    std::vector<std::thread> pool;
};

int main(int argc, char *argv[]) {
    std::vector<std::string> names;
    std::vector<std::thread> threadPool;
    std::thread th1;

    std::cout << "buna dimineata!\n";
    return 0;
}
