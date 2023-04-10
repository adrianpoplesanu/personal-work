#include <iostream>
#include <chrono>
#include <thread>

int contor;

void worker() {
    std::cout << "running a thread\n";
    for (int i = 0; i < 100; i++) {
        contor++;
        std::cout << i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "finishing a thread\n";
}

int main(int argc, char* argv[]) {
    // testing threads for ad
    contor = 0;

    std::thread th1(worker); // asta e echivalentul lui start() din java
    //th1.detach();
    /*if (th1.joinable()) {
        std::cout << "aaa";
        th1.join();
    }*/
    th1.join(); // asta e echivalentul lui join() din java

    std::thread th2(worker); // asta e echivalentul lui start() din java
    //th2.detach();
    /*if (th2.joinable()) {
        std::cout << "bbb";
        th2.join();
    }*/
    th2.join(); // asta e echivalentul lui join() din java

    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "contor: " << contor << "\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    return 0;
}