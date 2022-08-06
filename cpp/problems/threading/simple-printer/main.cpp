#include <iostream>
#include <thread>

void worker(int id, int factor) {
    for (int i = 0; i < 100; i++) {
        std::cout << id << ":::" << i * factor << "\n";
    }
}

int main(int argc, char* argv[]) {
    //...
    std::thread th0(worker, 0, 1);
    std::thread th1(worker, 1, 2);
    std::thread th2(worker, 2, 3);
    std::thread th3(worker, 3, 4);

    th0.join();
    th1.join();
    th2.join();
    th3.join();
}
