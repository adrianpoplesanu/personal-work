#include <iostream>
#include <thread>

class Environment {
public:
    int *contor;

    Environment() {
        contor = new int();
    }

    Environment* copy() {
        Environment* result = new Environment();
        *(result->contor) = *contor;
        return result;
    }
};

void worker(Environment *env) {
    std::cout << "running a thread\n";
    for (int i = 0; i < 100; i++) {
        std::cout << i << "\n";
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        int c = *(env->contor) + 1;
        delete env->contor;
        env->contor = new int(c);
    }
    std::cout << "finishing a thread" << *(env->contor) << "\n";
}

int main(int argc, char *argv[]) {

    Environment *env = new Environment();

    std::thread th1(worker, env->copy());
    std::thread th2(worker, env->copy());
    std::thread th3(worker, env->copy());
    std::thread th4(worker, env->copy());


    th1.join();
    th2.join();
    th3.join();
    th4.join();

    return 0;
}