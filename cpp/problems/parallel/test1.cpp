#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

int main(int argc, char *argv[]) {
    int pid;
    cout << "consumer running...\n";
    while(1) {
        cout << "retrieving data\n";
        // TODO: collect data from somewhere
        // TODO: do the actual task
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    return 0;
}
