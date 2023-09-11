// asa nu merge, trebuie un thread master
#include <iostream>
#include <thread>
#include <vector>

std::vector<bool> is_idle;

void idle_worker(int i) {
    while (is_idle[i]) {
        //... maybe not
    }
}

void worker1() {
    for (int i = 0; i < 100; i++) {
        std::cout << i << '\n';
    }
}

void worker2() {
    for (int i = 0; i < 100; i++) {
        std::cout << i << '\n';
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::thread> pool;

    std::thread th1(worker1);
    th1.join();

    return 0;
}
