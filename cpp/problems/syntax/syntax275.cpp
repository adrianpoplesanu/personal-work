#include <iostream>
#include <chrono>
#include <thread>

int contor;

void worker() {
    std::cout << "running a thread\n";
    for (int i = 0; i < 100; i++) {
        contor++;
        std::cout << i << "\n";
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "finishing a thread\n";
}

class Ad_Thread {
public:
    std::thread *internal;

    Ad_Thread() {
        internal = NULL;
    }

    ~Ad_Thread() {
        //if (internal != NULL && internal->joinable()) {
        //    internal->join();
        //}
    }
};

int main(int argc, char* argv[]) {
    // testing threads for ad
    contor = 0;

    Ad_Thread* adThread1 = new Ad_Thread();
    std::thread *th1 = new std::thread(worker);
    adThread1->internal = th1;

    Ad_Thread* adThread2 = new Ad_Thread();
    std::thread *th2 = new std::thread(worker);
    adThread2->internal = th2;

    Ad_Thread* adThread3 = new Ad_Thread();
    std::thread *th3 = new std::thread(worker);
    adThread3->internal = th3;

    Ad_Thread* adThread4 = new Ad_Thread();
    std::thread *th4 = new std::thread(worker);
    adThread4->internal = th4;

    adThread1->internal->join();
    //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    adThread2->internal->join();
    adThread3->internal->join();
    adThread4->internal->join();

    //delete adThread;
    //delete adThread2;
}