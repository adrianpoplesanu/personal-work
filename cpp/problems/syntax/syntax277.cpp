#include <iostream>
#include <thread>

enum Ad_Type {
    INTEGER
};

class Ad_Int {
public:
    int value;
    Ad_Type type;

    Ad_Int(int v) {
        type = INTEGER;
        value = v;
    }
};

class Environment {
public:
    Ad_Int *contor;

    Environment() {
        contor = new Ad_Int(55);
    }
};

void worker(Environment *env, int delay) {
    std::cout << "running a thread\n";
    std::cout << "sleeping for " << delay << "miliseconds\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    std::cout << "type: " << env->contor->type;
    std::cout << "contor: " << env->contor->value + 4;
    delete env->contor;
    std::cout << "finishing a thread" << "\n";
}

int main(int argc, char *argv[]) {

    Environment *env = new Environment();

    std::thread th1(worker, env, 10);
    std::thread th2(worker, env, 20);
    std::thread th3(worker, env, 30);
    std::thread th4(worker, env, 40);


    th1.join();
    th2.join();
    th3.join();
    th4.join();

    return 0;
}