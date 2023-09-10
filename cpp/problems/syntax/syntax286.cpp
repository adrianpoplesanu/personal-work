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
        pool.push_back(NULL);
    }
}

void schedulerWorker() {
    std::cout << "schedulerWorker started\n";
    while (true) {
        if (!poolActive) {
            break;
        }
        for (int i = 0; i < NUM_THREADS; i++) {
            if (pool[i] != NULL && threads_status[i] == "CALL_JOIN" && pool[i]->joinable()) {
                pool[i]->join();
                delete pool[i];
                pool[i] = NULL;
                threads_status[i] = "IDLE";
            }
        }
    }
    std::cout << "schedulerWorker shut down\n";
}

void worker(int k) {
    std::cout << "running worker thread " << k << "\n";
    for (int i = 0; i < 100; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "stopping worker thread " << k << "\n";
    threads_status[k] = "CALL_JOIN";
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
        if (line == "start") {
            // add thread to the queue
            int i = 0;
            while (i < NUM_THREADS && threads_status[i] != "IDLE") {
                i++;
            }
            if (i < NUM_THREADS) {
                std::cout << "thread " << i << " scheduled\n";
                threads_status[i] = "RUNNING";
                //std::thread th1(worker, i);
                std::thread *th1 = new std::thread(worker, i);
                pool[i] = th1;
            }
        }
        if (line == "exit") {
            poolActive = false;
            std::cout << "shutting down\n";
            break;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        if (threads_status[i] == "RUNNING" || threads_status[i] == "CALL_JOIN") {
            if (pool[i] != NULL && pool[i]->joinable()) {
                pool[i]->join();
            }
        }
    }

    if ((*schedulerThread).joinable()) {
        (*schedulerThread).join();
    }
    return 0;
}
