#include <iostream>
#include <thread>
#include <map>

enum Ad_Type {
    INTEGER
};

class Ad_Int {
public:
    int value;
    Ad_Type type;
    Ad_Int *next;
    Ad_Int *prev;

    Ad_Int(int v) {
        type = INTEGER;
        value = v;
    }
};

class Environment {
public:
    std::map<std::string, Ad_Int*> store;

    Environment() {
        //...
    }
};

class GarbageCollector {
public:
    Ad_Int *head, *tail;
    void addObject() {

    }
    void markObjects() {

    }
    void sweepObject() {

    }
};

void worker(Environment *env, GarbageCollector *gc, int delay) {
    std::cout << "running a thread\n";
    std::cout << "sleeping for " << delay << "miliseconds\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    //Ad_Type type = env->store["aaa"]->type; // linia asta ridica genul de eroare pe care il gasesc si in ad
    gc->markObjects();
    gc->sweepObject();
    //delete env->contor;
    std::cout << "finishing a thread\n";
}

int main(int argc, char *argv[]) {

    Environment *env = new Environment();
    GarbageCollector *gc = new GarbageCollector();

    std::thread th1(worker, env, gc, 10);
    std::thread th2(worker, env, gc, 20);
    std::thread th3(worker, env, gc, 30);
    std::thread th4(worker, env, gc, 40);


    th1.join();
    th2.join();
    th3.join();
    th4.join();

    return 0;
}