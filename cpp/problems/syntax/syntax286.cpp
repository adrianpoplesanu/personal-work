#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

std::vector<std::string> threads_status;
std::thread *threads;
std::vector<std::thread*> pool;
std::thread *schedulerThread;
bool poolRunning = false;
bool poolActive = true;

int NUM_THREADS = 5;

void init() {
    for (int i = 0; i < NUM_THREADS; i++) {
        threads_status.push_back("IDLE");
    }
}

void schedulerWorker() {
    std::cout << "schedulerWorker started\n";
    while (true) {
        if (!poolActive) {
            break;
        }
    }
    std::cout << "schedulerWorker shut down\n";
}

void worker() {

}

int main(int argc, char *argv[]) {
    init();
    std::thread th1(schedulerWorker);
    schedulerThread = &th1;

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    while(true) {
        std::cout << ">> ";
        std::string line;
        std::getline(std::cin, line);
        if (line == "exit") {
            poolActive = false;
            std::cout << "shutting down\n";
            break;
        }
    }


    if ((*schedulerThread).joinable()) {
        (*schedulerThread).join();
    }
    return 0;
}
