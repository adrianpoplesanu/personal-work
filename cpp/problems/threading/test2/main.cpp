#include <iostream>
#include <thread>
using namespace std;

void thread_function(int tid, int repeats, string message) {
    cout << "starting thread id: " << tid << endl;
    for (int i = 0; i < repeats; i++) cout << "thread" << tid << ": " <<  message << endl;
    cout << "ending thread id: " << tid << endl;
}

int main(int argc, char *argv[]) {
    int repeats = 10;
    string message = "neata!";
    thread threads[3];
    for (int i = 0; i < 3; i++) {
        threads[i] = thread(thread_function, i, repeats, message);
    }
    for (int i = 0; i < 3; i++) {
        threads[i].join();
    }
    return 0;
}
