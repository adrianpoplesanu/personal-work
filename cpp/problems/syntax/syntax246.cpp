#include <iostream>
#include <map>

class AdObject {
public:
    int a = 5;
};

class Environment {
public:
    std::map<std::string, AdObject*> store;
    ~Environment() {
        for(std::map<std::string, AdObject* >::const_iterator it = store.begin(); it != store.end(); ++it) {
            delete it->second;
        }
    }
};

int main(int argc, char* argv[]) {
    Environment *e = new Environment();
    AdObject *obj = new AdObject();
    e->store["obj"] = obj;
    std::cout << e->store["obj"]->a << "\n";
    delete e;
    return 0;
}
