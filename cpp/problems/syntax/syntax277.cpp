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
    bool marked;

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

    GarbageCollector() {
        head = tail = NULL;
    }

    void addObject(Ad_Int *obj) {
        if (tail == NULL) {
            head = obj;
            tail = obj;
            head->prev = NULL;
            head->next = NULL;
        } else {
            obj->prev = tail;
            obj->next = NULL;
            tail->next = obj;
        }
    }
    void markObjects() {
        Ad_Int* current = head;
        while (current != NULL) {
            current->marked = false;
            current = current->next;
        }
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