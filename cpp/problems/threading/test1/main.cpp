#include <iostream>
#include <thread>
using namespace std;

void thread_function() {
    for (int i = 0; i < 10; i++) cout << "thread function Executing" << endl;
}

int main(int argc, char *argv[]) {
    thread threadObj(thread_function);
    for (int i = 0; i < 10; i++) cout << "Displayy From MainThread" << endl;
    threadObj.join();
    cout << "Exit of Main function" << endl;
    return 0;
}
