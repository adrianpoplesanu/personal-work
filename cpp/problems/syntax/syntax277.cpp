#include <iostream>
#include <thread>
#include <map>
#include <vector>

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

    Ad_Int* get(std::string key) {
        return store[key];
    }

    void set(std::string key, Ad_Int* obj) {
        store[key] = obj;
    }
};

class GarbageCollector {
public:
    Ad_Int *head, *tail;
    std::vector<Environment*> gc_environments;

    GarbageCollector() {
        head = tail = NULL;
    }

    void addEnvironment(Environment* env) {
        gc_environments.push_back(env);
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
        Ad_Int* current = head;
        while (current != NULL) {
            if (!current->marked) {
                Ad_Int* target = current;
                current->prev->next = current->next;
                current->next->prev = current->prev;
                current = current->next;
                delete target;
            } else {
                current = current->next;
            }
        }
    }
};

void worker(Environment *env, GarbageCollector *gc, int delay) {
    std::cout << "running a thread\n";
    std::cout << "sleeping for " << delay << "miliseconds\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    std::cout << env->get("contor")->value << "\n";
    //Ad_Type type = env->store["aaa"]->type; // linia asta ridica genul de eroare pe care il gasesc si in ad
    gc->markObjects();
    gc->sweepObject();
    //delete env->contor;
    std::cout << "finishing a thread\n";
}

int main(int argc, char *argv[]) {

    Environment *env = new Environment();
    GarbageCollector *gc = new GarbageCollector();
    Ad_Int *var = new Ad_Int(55);
    gc->addObject(var);
    env->set("contor", var);

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